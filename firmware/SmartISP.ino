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
    Serial.print("Low fuse: ");
    Serial.print(fuse.low, HEX);
    Serial.print(" = ");
    Serial.println(fuse.low, BIN);

    Serial.print("High fuse: ");
    Serial.print(fuse.high, HEX);
    Serial.print(" = ");
    Serial.println(fuse.high, BIN);

    Serial.print("Extended fuse: ");
    Serial.print(fuse.extended, HEX);
    Serial.print(" = ");
    Serial.println(fuse.extended, BIN);

    Serial.print("Lock Byte: ");
    Serial.print(fuse.lock, HEX);
    Serial.print(" = ");
    Serial.println(fuse.lock, BIN);

    Serial.print("Calibration byte: ");
    Serial.print(fuse.calibration, HEX);
    Serial.print(" = ");
    Serial.println(fuse.calibration, BIN);
}

void printSignature(const Signature* signature)
{
    Serial.print("Processor = ");
    Serial.println(signature->desc);

    Serial.print("Flash memory size = ");
    Serial.print(signature->flashSize, DEC);
    Serial.println(" bytes.");

    Serial.print("Flash page size = ");
    Serial.print(signature->pageSize, DEC);
    Serial.println(" bytes.");

    Serial.print("Bootloader section size = ");
    Serial.print(signature->baseBootSize, DEC);
    Serial.println(" (*1/2/4/8) bytes.");
}

void setup()
{
    Serial.begin(9600);
    while (!Serial) {}

    Serial.println("\n\nStone Labs. Smart ISP");
    Serial.println("Verion " XSTR(__PVERSION__) " compiled at " __DATE__ " " __TIME__ " using Arduino IDE version " XSTR(ARDUINO));
    

    //
    // SD CARD
    //

    Serial.print("-> Initializing SD card...");
    SdFat sd;
    if (!sd.begin(3, SPI_HALF_SPEED)) 
        sd.initErrorHalt();

    Serial.println(" [OK]");

    SdFile file;
    // open next file in root.  The volume working directory, vwd, is root
    while (file.openNext(sd.vwd(), O_READ)) 
    {
        Serial.print("|-- ");
        file.printName(&Serial);
        Serial.print(" ");
        file.printModifyDateTime(&Serial);
        Serial.println("");
        file.close();
    }


    //
    // PROGRAMMER
    //
    Serial.println("\nEnter 'G' to start.");
    while (Serial.read() != 'G');

    Serial.println("\n-> Starting 8 Mhz Clock on Pin 9.");

    // set up 8 MHz timer on PIN 10 (OC1B)
    // https://arduino.stackexchange.com/questions/16698/arduino-constant-clock-output
    pinMode(10, OUTPUT);
    // set up Timer 1
    TCCR1A = bit(COM1B0);  // toggle OC1B on Compare Match
    TCCR1B = bit(WGM12) | bit(CS10);   // CTC, no prescaling
    OCR1B = 0;       // output every cycle

    using namespace programmer;

    Serial.println("\n-> Entering Programming mode.");
    BBProgrammer programmer = BBProgrammer(P_SCK, P_MOSI, P_MISO, P_RESET);
    if (!programmer.startProgramming(5))
        return;


    delay(1000);
    Serial.println("\n-> Reading Signature.");
    if (!programmer.readSignature())
    {
        Serial.println("Chip locked! Issue erase. [ABORT]");
        return;
    }
    const Signature* signature = programmer.getSignature();
    printSignature(signature);

    delay(1000);
    Serial.print("\n-> Erasing CHIP.");
    //programmer.erase();
    Serial.println(" [OK]");

    delay(1000);
    Serial.print("\n-> Reading Fuses.");
    programmer.readFuses();
    Serial.println(" [OK]");
    const BBProgrammer::Fuse& fuse = programmer.getFuses();
    printFuses(fuse);

    Serial.println("\n-> Reading HEX source /Blink.hex.");
    if (!file.open("Blink.hex"), O_READ)
    {
        Serial.println("Error: Couldn't open source file.");
        return;
    }

    char lineBuffer[HEX_LINE_LENGTH];
    unsigned int index = 0; // Current write index in `lineBuffer`
    while (file.available()) {
        lineBuffer[index] = file.read();
        if (lineBuffer[index] == 0x0A) // Newline byte in ASCII
        {
            // lineBuffer contains a single line with newline at the end
            Serial.print("Processing: ");
            Serial.print(lineBuffer);

            // Clear all writen bytes and return to first.
            // index will be -1 after this but increased below
            do { lineBuffer[index] = 0x00; } while (index-- > 0);
        }
        index++;
    }
    file.close();

    delay(1000);
    Serial.println("\n-> Leaving Programming mode.");
    programmer.stopProgramming();
}

void loop() 
{
  
}

