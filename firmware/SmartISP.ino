#define XSTR(s) STR(s)
#define STR(s) #s

#define __PVERSION__ "pre-0.01"
#define DEBUG false

// Line format :
// 
// : nnaaaatt(data)ss
// 
// Where :
// : = a colon
// 
// (All of below in hex format)
// 
// nn = length of data part
// aaaa = address(eg.where to write data)
// tt = transaction type:
//  00 = data
//  01 = end of file
//  02 = extended segment address (data * 0x10 is added to all subsequent data entries)
//  03 = start segment address  (NOT SUPPORTED)
//  04 = linear address         (NOT SUPPORTED)
//  05 = start linear address   (NOT SUPPORTED)
// (data) = variable length data (most common are 16 and 32 bytes)
// ss = sumcheck
// 
//
// Line length for max 32 data bytes (64 chars):
#define HEX_LINE_LENGTH 76
#define HEX_MAX_DATALEN 32

// External Dependencies
#include <SPI.h>
#include <SdFat.h>

#include "src/programmer/bbprogrammer.h"

#define P_SCK 7
#define P_MISO 6
#define P_MOSI 5
#define P_RESET 4

void printFuses(const programmer::BBProgrammer::Fuse& fuse)
{
    Serial.print(F("Low fuse: "));
    Serial.print(fuse.low, HEX);
    Serial.print(F(" = "));
    Serial.println(fuse.low, BIN);

    Serial.print(F("High fuse: "));
    Serial.print(fuse.high, HEX);
    Serial.print(F(" = "));
    Serial.println(fuse.high, BIN);

    Serial.print(F("Extended fuse: "));
    Serial.print(fuse.extended, HEX);
    Serial.print(F(" = "));
    Serial.println(fuse.extended, BIN);

    Serial.print(F("Lock Byte: "));
    Serial.print(fuse.lock, HEX);
    Serial.print(F(" = "));
    Serial.println(fuse.lock, BIN);

    Serial.print(F("Calibration byte: "));
    Serial.print(fuse.calibration, HEX);
    Serial.print(F(" = "));
    Serial.println(fuse.calibration, BIN);
}

void printSignature(const Signature* signature)
{
    Serial.print(F("Processor = "));
    Serial.println(signature->desc);

    Serial.print(F("Flash memory size = "));
    Serial.print(signature->flashSize, DEC);
    Serial.println(F(" bytes."));

    Serial.print(F("Flash page size = "));
    Serial.print(signature->pageSize, DEC);
    Serial.println(F(" bytes."));

    Serial.print(F("Bootloader section size = "));
    Serial.print(signature->baseBootSize, DEC);
    Serial.println(F(" (*1/2/4/8) bytes."));
}

byte hexton(byte h)
{
    // Convert ascii HEX to number
    if (h >= '0' && h <= '9')
        return(h - '0');
    if (h >= 'A' && h <= 'F')
        return((h - 'A') + 10);

    Serial.println(F("Invalid HEX."));
    while (true) {};
}
byte twos_complement(byte val)
{
    return -(unsigned int)val;
}

// Returns lowest address behind current page. (so min addr >= pageaddr + pagesize) 
// More information on HEX file: https://en.wikipedia.org/wiki/Intel_HEX
unsigned long readImagePage(SdFile *file, const unsigned long flashsize, const unsigned long pageaddr, const unsigned long pagesize, byte* pagebuffer)
{
    // Back to begining of file.
    file->rewind();

    // 'empty' the page by filling it with 0xFF's
    for (unsigned long i = 0; i < pagesize; i++)
        pagebuffer[i] = 0xFF;

    // Allocate and initialize line buffer
    char* lineBuffer = new char[HEX_LINE_LENGTH];
    for (unsigned int i = 0; i < HEX_LINE_LENGTH; i++)
        lineBuffer[i] = 0x00;

    unsigned int index = 0; // Current write index in `lineBuffer`
    char charBuffer;

    // Metadata of lines
    byte l_bytecount = 0x0;
    unsigned long l_address_offset = 0x0;
    unsigned long l_address = 0x0;
    byte l_recordtype = 0x0;
    byte l_checksum = 0x0;

    // Return variable:
    // Smallest address after current frame
    unsigned long smallestAfter = 0UL - 1UL; // Largest unsigned long

    // Read file 
    while (file->available()) {
        charBuffer = file->read();

        if (charBuffer == 0x13) // Carriage return in ASCII
            continue; //ignore CR
        else if (charBuffer == 0x0A) // Newline byte in ASCII
        {
            // lineBuffer contains a single line without newline at the end
#if DEBUG            
            Serial.println(lineBuffer);
#endif

            if (lineBuffer[0] != ':')
            {
                Serial.println(F("Invalid hex file (1)"));
                while (true) {};
            }
            
            // Read line `metadata`
            l_bytecount = hexton(lineBuffer[1]) << 4 | hexton(lineBuffer[2]);
            l_address = l_address | hexton(lineBuffer[3]) << 12;
            l_address = l_address | hexton(lineBuffer[4]) << 8;
            l_address = l_address | hexton(lineBuffer[5]) << 4;
            l_address = l_address | hexton(lineBuffer[6]) << 0;
            l_recordtype = hexton(lineBuffer[7]) << 4 | hexton(lineBuffer[8]);

            if (l_bytecount > HEX_MAX_DATALEN)
            {
                Serial.println(F("HEX Data too long to process"));
                while (true) {};
            }
            l_checksum = hexton(lineBuffer[9 + l_bytecount *2]) << 4 | hexton(lineBuffer[10 + l_bytecount * 2]);

            if (l_bytecount > HEX_MAX_DATALEN)
            {
                Serial.println(F("HEX Data too long to process"));
                while (true) {};
            }
            if (l_recordtype < 0 || l_recordtype > 2)
            {
                Serial.println(F("Unsupported HEX entry."));
                while (true) {};
            }

            // Checksum check
            byte calcCheckSum = 0x00;
            for (byte i = 1; i < 9 + l_bytecount * 2; i += 2) // From 1 to last databyte
                calcCheckSum += hexton(lineBuffer[i + 0]) << 4 |
                hexton(lineBuffer[i + 1]);

            if (twos_complement(calcCheckSum) != l_checksum)
            {
                Serial.println(F("Line checksum mismatch!"));
                while (true) {};
            }

            // 'Extended Segment Address' entry
            // Data field (16 bits) is multiplied by 16 and added to each
            // subsequent data entry address
            if (l_recordtype == 0x02)
            {
                // Get 16 bit data field
                l_address_offset = 0x00;
                l_address_offset = l_address_offset | hexton(lineBuffer[9]) << 12;
                l_address_offset = l_address_offset | hexton(lineBuffer[10]) << 8;
                l_address_offset = l_address_offset | hexton(lineBuffer[11]) << 4;
                l_address_offset = l_address_offset | hexton(lineBuffer[12]) << 0;

                l_address_offset *= 0x10; // Multiply by 16

#if DEBUG
                Serial.print(F("Read Extended Segment Address record: "));
                Serial.print(l_address_offset, HEX);
                Serial.println(F(" set as offset!"));
#endif
            }
            // Apply offset from previous 'Extended Segment Addresses'
            l_address += l_address_offset;

            // Data Type
            if (l_recordtype == 0x00)
            {
                // Check for valid Data record address range (i.e. is it in flash bounds?)
                if (l_address + l_bytecount > flashsize)
                {
                    Serial.println(F("HEX not in flash bounds!"));
                    while (true) {};
                }

                // Page adding
                for (byte i = 9; i < 9 + l_bytecount * 2; i += 2) // From first to last databyte
                {
                    // Write to page buffer if address is in current `page area`
                    if (l_address >= pageaddr && l_address - pageaddr < pagesize)
                    {
                        pagebuffer[l_address - pageaddr] =
                            hexton(lineBuffer[i + 0]) << 4 | hexton(lineBuffer[i + 1]);
#if DEBUG
                        Serial.print(F("Writing to paging buffer: "));
                        Serial.print(hexton(lineBuffer[i + 0]) << 4 | hexton(lineBuffer[i + 1]), HEX);
                        Serial.print(F(" at "));
                        Serial.println(l_address - pageaddr, HEX);
#endif
                    }
                    if (l_address >= pageaddr + pagesize && l_address < smallestAfter)
                    {
                        smallestAfter = l_address;
                    }
                    l_address++;
                }
            }

            // Clear all writen bytes and return to first.
            // index will be -1 after this but increased below
            do { lineBuffer[index] = 0x00; } while (index-- > 0);
        }
        else
            lineBuffer[index] = charBuffer; // Write character to lineBuffer

        index++;
    }

    // Clean up
    delete[] lineBuffer;

    return smallestAfter;
}

void setup()
{
    Serial.begin(115200);
    while (!Serial) {}

    Serial.println(F("\n\nStone Labs. Smart ISP"));
    Serial.println("Verion " XSTR(__PVERSION__) " compiled at " __DATE__ " " __TIME__ " using Arduino IDE version " XSTR(ARDUINO));
    

    //
    // SD CARD
    //

    Serial.print(F("-> Initializing SD card..."));
    SdFat sd;
    if (!sd.begin(3, SPI_HALF_SPEED)) 
        sd.initErrorHalt();

    Serial.println(F(" [OK]"));

    SdFile file;
    // open next file in root.  The volume working directory, vwd, is root
    while (file.openNext(sd.vwd(), O_READ)) 
    {
        Serial.print(F("|-- "));
        file.printName(&Serial);
        Serial.print(F(" "));
        file.printModifyDateTime(&Serial);
        Serial.println(F(""));
        file.close();
    }


    //
    // PROGRAMMER
    //
    Serial.println(F("\nEnter 'G' to start."));
    while (Serial.read() != 'G');

    Serial.println(F("\n-> Starting 8 Mhz Clock on Pin 9."));

    // set up 8 MHz timer on PIN 10 (OC1B)
    // https://arduino.stackexchange.com/questions/16698/arduino-constant-clock-output
    pinMode(10, OUTPUT);
    // set up Timer 1
    TCCR1A = bit(COM1B0);  // toggle OC1B on Compare Match
    TCCR1B = bit(WGM12) | bit(CS10);   // CTC, no prescaling
    OCR1B = 0;       // output every cycle

    using namespace programmer;

    Serial.println(F("\n-> Entering Programming mode."));
    BBProgrammer programmer = BBProgrammer(P_SCK, P_MOSI, P_MISO, P_RESET);
    if (!programmer.startProgramming(5))
        return;


    delay(1000);
    Serial.println(F("\n-> Reading Signature."));
    if (!programmer.readSignature())
    {
        Serial.println(F("Chip locked! Issue erase. [ABORT]"));
        return;
    }
    const Signature* signature = programmer.getSignature();
    printSignature(signature);

    delay(1000);
    Serial.print(F("\n-> Erasing CHIP."));
    //programmer.erase();
    Serial.println(F(" [OK]"));

    delay(1000);
    Serial.print(F("\n-> Reading Fuses."));
    programmer.readFuses();
    Serial.println(F(" [OK]"));
    const BBProgrammer::Fuse& fuse = programmer.getFuses();
    printFuses(fuse);

    Serial.println(F("\n-> Flashing HEX source /optiboot.hex."));
    if (!file.open("optiboot.hex"), O_READ)
    {
        Serial.println(F("Error: Couldn't open source file."));
        return;
    }
    
    // Iterate over all pages in target flash
    // and fill them with readImagePage(...).
    // Then write them to the target.
    byte* page = new byte[signature->pageSize];
    unsigned long pageaddr = 0x00;
    unsigned long nextSmallest = 0x00; // Next smallest address
    
    // If a bootloader is found at the entry points
    // it will be save in lowestBootLoader.
    unsigned long lowestBootLoader = signature->flashSize;
    while (pageaddr < signature->flashSize) {
//#if DEBUG
        Serial.print(F("Processing page 0x"));
        Serial.print(pageaddr, HEX);
        Serial.print(F(" - 0x"));
        Serial.print(pageaddr + signature->pageSize - 1, HEX);
        Serial.print(F("..."));
//#endif

        // Skip if next smallest address is not inside this page.
        if (nextSmallest <= pageaddr + signature->pageSize - 1)
        {
            nextSmallest = readImagePage(&file, signature->flashSize, pageaddr, signature->pageSize, page);

            boolean blankpage = true;
            for (uint8_t i = 0; i < signature->pageSize; i++)
                if (page[i] != 0xFF)
                    blankpage = false;

            if (!blankpage)
            {
//#if DEBUG
                Serial.print(F(" [OK: NS="));
                Serial.print(nextSmallest, HEX);
                Serial.print(F("] -> Flashing..."));
//#endif
                
                programmer.flashPage(pageaddr, page);

//#if DEBUG
                Serial.print(F(" [FLASHED]"));
//#endif

                // Check bootloader positions *(1/2/4/8)
                for (int i = 1; i <= 8; i *= 2)
                {
                    // Possible bootlaoder position in current page?
                    unsigned long bootloaderAddress = signature->flashSize - signature->baseBootSize * i;
                    if (bootloaderAddress < pageaddr || bootloaderAddress > pageaddr + signature->pageSize - 1)
                        continue; // If not skip this position

                    unsigned long bootloaderPageAddress = bootloaderAddress - pageaddr;

                    // Check if bootloader position caintains instruction
                    if (page[bootloaderPageAddress] != 0xFF)
                    {
//#if DEBUG
                        Serial.print(F(" Found bootloader at 0x"));
                        Serial.print(signature->flashSize - signature->baseBootSize, HEX);
//#endif
                        if (bootloaderAddress < lowestBootLoader)
                            lowestBootLoader = bootloaderAddress;
                    }
                }
//#if DEBUG
                Serial.println();
//#endif
            }
//#if DEBUG
            else
            {
                Serial.print(F(" [EMPTY NS="));
                Serial.print(nextSmallest, HEX);
                Serial.println(F("]"));
            }
//#endif
        }
//#if DEBUG
        else
            Serial.println(F(" [SKIP]"));
//#endif
        pageaddr += signature->pageSize;
    }

    file.close();
    delete[] page;

    // Flashing done. Show user feedback
    Serial.println(F("Flashing complete."));
    if (lowestBootLoader == signature->flashSize)
        Serial.println(F("No bootlaoder detected."));
    else
    {
        Serial.print(F("Bootloader detected at 0x"));
        Serial.println(lowestBootLoader, HEX);
        Serial.println(F("Changing bootloader fuse... [TODO]"));
    }


    delay(1000);
    Serial.println(F("\n-> Leaving Programming mode."));
    programmer.stopProgramming();
}

void loop() 
{
  
}

