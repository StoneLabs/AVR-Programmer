#include "helper.h"

void printFuses(const programmer::BBProgrammer::Fuse& fuse)
{
    Debug(DEBUG_INFO, F("Low fuse: "));
    Debug(DEBUG_INFO, fuse.low, HEX);
    Debug(DEBUG_INFO, F(" = "));
    Debugln(DEBUG_INFO, fuse.low, BIN);

    Debug(DEBUG_INFO, F("High fuse: "));
    Debug(DEBUG_INFO, fuse.high, HEX);
    Debug(DEBUG_INFO, F(" = "));
    Debugln(DEBUG_INFO, fuse.high, BIN);

    Debug(DEBUG_INFO, F("Extended fuse: "));
    Debug(DEBUG_INFO, fuse.extended, HEX);
    Debug(DEBUG_INFO, F(" = "));
    Debugln(DEBUG_INFO, fuse.extended, BIN);

    Debug(DEBUG_INFO, F("Lock Byte: "));
    Debug(DEBUG_INFO, fuse.lock, HEX);
    Debug(DEBUG_INFO, F(" = "));
    Debugln(DEBUG_INFO, fuse.lock, BIN);

    Debug(DEBUG_INFO, F("Calibration byte: "));
    Debug(DEBUG_INFO, fuse.calibration, HEX);
    Debug(DEBUG_INFO, F(" = "));
    Debugln(DEBUG_INFO, fuse.calibration, BIN);
}

void printSignature(const Signature* signature)
{
    Debug(DEBUG_INFO, F("Processor = "));
    Debugln(DEBUG_INFO, signature->desc);

    Debug(DEBUG_INFO, F("Flash memory size = "));
    Debug(DEBUG_INFO, signature->flashSize, DEC);
    Debugln(DEBUG_INFO, F(" bytes."));

    Debug(DEBUG_INFO, F("Flash page size = "));
    Debug(DEBUG_INFO, signature->pageSize, DEC);
    Debugln(DEBUG_INFO, F(" bytes."));

    Debug(DEBUG_INFO, F("Bootloader section size = "));
    Debug(DEBUG_INFO, signature->baseBootSize, DEC);
    Debugln(DEBUG_INFO, F(" (*1/2/4/8) bytes."));
}

byte hexton(byte h, byte& errorFlag)
{
    // Convert ascii HEX to number
    if (h >= '0' && h <= '9')
        return(h - '0');
    if (h >= 'A' && h <= 'F')
        return((h - 'A') + 10);

    Debugln(DEBUG_INFO, F("Invalid HEX number."));
    errorFlag = error_hexCharSymbol;
    return 0;
}
byte twos_complement(byte val)
{
    return -(unsigned int)val;
}

// Returns lowest address behind current page. (so min addr >= pageaddr + pagesize) 
// More information on HEX file: https://en.wikipedia.org/wiki/Intel_HEX
unsigned long readImagePage(SdFile* file, const unsigned long flashsize, const unsigned long pageaddr, const unsigned long pagesize, byte* pagebuffer, byte& errorFlag)
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
            Debugln(DEBUG_VERBOSE, lineBuffer);

            // Check for colon at line begining
            if (lineBuffer[0] != ':')
            {
                Debugln(DEBUG_INFO, F("Invalid hex file (1)"));
                errorFlag = error_hexInvalid;
                delete[] lineBuffer;
                return 0x00UL;
            }

            // Read line `metadata`
            l_bytecount = hexton(lineBuffer[1], errorFlag) << 4 | hexton(lineBuffer[2], errorFlag);
            l_address = hexton(lineBuffer[3], errorFlag) << 12;
            l_address = l_address | hexton(lineBuffer[4], errorFlag) << 8;
            l_address = l_address | hexton(lineBuffer[5], errorFlag) << 4;
            l_address = l_address | hexton(lineBuffer[6], errorFlag) << 0;
            l_recordtype = hexton(lineBuffer[7], errorFlag) << 4 | hexton(lineBuffer[8], errorFlag);

            if (l_bytecount > HEX_MAX_DATALEN)
            {
                Debugln(DEBUG_INFO, F("HEX Row data too long to process"));
                errorFlag = error_hexLineTooLong;
                delete[] lineBuffer;
                return 0x00UL;
            }

            l_checksum = hexton(lineBuffer[9 + l_bytecount * 2], errorFlag) << 4 | hexton(lineBuffer[10 + l_bytecount * 2], errorFlag);

            if (l_recordtype < 0 || l_recordtype > 3)
            {
                Debugln(DEBUG_INFO, F("Unsupported HEX entry."));
                errorFlag = error_hexUnsupportedEntry;
                delete[] lineBuffer;
                return 0x00UL;
            }

            if (l_recordtype == 3)
                Debugln(DEBUG_VERBOSE, F("HEX contains 'Start Segment Address'. Entry will be ignored."));

            // Checksum check
            byte calcCheckSum = 0x00;
            for (byte i = 1; i < 9 + l_bytecount * 2; i += 2) // From 1 to last databyte
                calcCheckSum += hexton(lineBuffer[i + 0], errorFlag) << 4 |
                hexton(lineBuffer[i + 1], errorFlag);

            if (twos_complement(calcCheckSum) != l_checksum)
            {
                Debugln(DEBUG_INFO, F("Line checksum mismatch!"));
                errorFlag = error_hexCheckSum;
                delete[] lineBuffer;
                return 0x00UL;
            }

            // 'Extended Segment Address' entry
            // Data field (16 bits) is multiplied by 16 and added to each
            // subsequent data entry address
            if (l_recordtype == 0x02)
            {
                // Get 16 bit data field
                l_address_offset = 0x00;
                l_address_offset = l_address_offset | hexton(lineBuffer[9], errorFlag) << 12;
                l_address_offset = l_address_offset | hexton(lineBuffer[10], errorFlag) << 8;
                l_address_offset = l_address_offset | hexton(lineBuffer[11], errorFlag) << 4;
                l_address_offset = l_address_offset | hexton(lineBuffer[12], errorFlag) << 0;

                l_address_offset *= 0x10; // Multiply by 16

                Debug(DEBUG_VERBOSE, F("Read Extended Segment Address record: "));
                Debug(DEBUG_VERBOSE, l_address_offset, HEX);
                Debugln(DEBUG_VERBOSE, F(" set as offset!"));
            }
            // Apply offset from previous 'Extended Segment Addresses'
            l_address += l_address_offset;

            // Data Type
            if (l_recordtype == 0x00)
            {
                // Check for valid Data record address range (i.e. is it in flash bounds?)
                if (l_address + l_bytecount > flashsize)
                {
                    Debugln(DEBUG_INFO, F("HEX not in flash bounds!"));
                    errorFlag = error_hexFlashBounds;
                    delete[] lineBuffer;
                    return 0x00UL;
                }

                // Page adding
                for (byte i = 9; i < 9 + l_bytecount * 2; i += 2) // From first to last databyte
                {
                    // Write to page buffer if address is in current `page area`
                    if (l_address >= pageaddr && l_address - pageaddr < pagesize)
                    {
                        pagebuffer[l_address - pageaddr] =
                            hexton(lineBuffer[i + 0], errorFlag) << 4 | hexton(lineBuffer[i + 1], errorFlag);

                        Debug(DEBUG_VERBOSE, F("Writing to paging buffer: "));
                        Debug(DEBUG_VERBOSE, hexton(lineBuffer[i + 0], errorFlag) << 4 | hexton(lineBuffer[i + 1], errorFlag), HEX);
                        Debug(DEBUG_VERBOSE, F(" at "));
                        Debugln(DEBUG_VERBOSE, l_address - pageaddr, HEX);
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
        {
            // Check if line is too long for buffer
            if (index >= HEX_LINE_LENGTH)
            {
                Debugln(DEBUG_INFO, F("HEX line too long!"));
                errorFlag = error_hexLineTooLong;
                delete[] lineBuffer;
                return 0x00UL;
            }

            lineBuffer[index] = charBuffer; // Write character to lineBuffer
        }

        index++;
    }

    // Clean up
    delete[] lineBuffer;

    return smallestAfter;
}

byte flashFile(SdFile* file, programmer::BBProgrammer* bbprogrammer)
{
    // Start programming mode
    Debugln(DEBUG_INFO, F("-> Entering Programming mode."));
    if (!bbprogrammer->startProgramming(5))
        return error_programmingMode;

    Debugln(DEBUG_INFO, F("-> Erasing chip."));
    bbprogrammer->erase();

    Debugln(DEBUG_INFO, F("-> Reading Fuses."));
    bbprogrammer->readFuses();
    printFuses(bbprogrammer->getFuses());
    const programmer::BBProgrammer::Fuse fuse = bbprogrammer->getFuses();

    Debugln(DEBUG_INFO, F("-> Reading signature."));
    bbprogrammer->readSignature();
    const Signature* signature = bbprogrammer->getSignature();
    
    Debugln(DEBUG_INFO, F("-> Flashing."));
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
        Debug(DEBUG_DEBUG, F("Processing page 0x"));
        Debug(DEBUG_DEBUG, pageaddr, HEX);
        Debug(DEBUG_DEBUG, F(" - 0x"));
        Debug(DEBUG_DEBUG, pageaddr + signature->pageSize - 1, HEX);
        Debug(DEBUG_DEBUG, F("..."));

        // Skip if next smallest address is not inside this page.
        if (nextSmallest <= pageaddr + signature->pageSize - 1)
        {
            byte errorBuffer = 0x00;
            nextSmallest = readImagePage(file, signature->flashSize, pageaddr, signature->pageSize, page, errorBuffer);
            if (errorBuffer > 0x00)
            {
                // An error was returned while filling the page buffer
                Debugln(DEBUG_DEBUG, F("Error flag returned by readImagePage(). Aborting flash."));
                bbprogrammer->stopProgramming();delete[] page;
                return errorBuffer;
            }

            boolean blankpage = true;
            for (uint8_t i = 0; i < signature->pageSize; i++)
                if (page[i] != 0xFF)
                    blankpage = false;

            if (!blankpage)
            {
                Debug(DEBUG_DEBUG, F(" [OK: NS="));
                Debug(DEBUG_DEBUG, nextSmallest, HEX);
                Debug(DEBUG_DEBUG, F("] -> Flashing..."));

                bbprogrammer->flashPage(pageaddr, page);

                Debug(DEBUG_DEBUG, F(" [FLASHED]"));

                // Check for bootloader if target has bootloader support
                if (signature->fuseWithBootloaderSize != NO_FUSE)
                {
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
                            Debug(DEBUG_DEBUG, F(" Found bootloader at 0x"));
                            Debug(DEBUG_DEBUG, signature->flashSize - signature->baseBootSize, HEX);
                            if (bootloaderAddress < lowestBootLoader)
                                lowestBootLoader = bootloaderAddress;
                        }
                    }
                }
                Debugln(DEBUG_DEBUG);
            }
            else
            {
                Debug(DEBUG_DEBUG, F(" [EMPTY NS="));
                Debug(DEBUG_DEBUG, nextSmallest, HEX);
                Debugln(DEBUG_DEBUG, F("]"));
            }
        }
        else
            Debugln(DEBUG_DEBUG, F(" [SKIP]"));
        pageaddr += signature->pageSize;
    }
    delete[] page;

    // Flashing done. Show user feedback
    Debugln(DEBUG_INFO, F("Flashing complete."));

    // If current chip supports bootloader, update corresponding fuse
    if (signature->fuseWithBootloaderSize == NO_FUSE)
    {
        // Debug output, that we'll not look for a bootloader for this chip.
        Debugln(DEBUG_DEBUG, F("No bootloader capability for target."));
    }
    else
    {
        // Change bootloader fuse in correct fuse byte
        if (signature->fuseWithBootloaderSize != highFuse &&
            signature->fuseWithBootloaderSize != extFuse)
        {
            // Bootloader setting not supported for current chip
            bbprogrammer->stopProgramming();
            return error_bootloaderSupport;
        }

        // Bootloader fuse bits appear to be the same on all AVR chips:
        // http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf page 243 and 239
        byte newBootloaderFuse = 0x0;
        byte oldBootloaderFuse = fuse.get(signature->fuseWithBootloaderSize);
        if (lowestBootLoader == signature->flashSize)
        {
            Debugln(DEBUG_INFO, F("No bootlaoder detected."));
            newBootloaderFuse = (oldBootloaderFuse & 0b11111000) | 0b001; // Application reset at 0x0000
        }
        else
        {
            Debug(DEBUG_INFO, F("Bootloader detected at 0x"));
            Debugln(DEBUG_INFO, lowestBootLoader, HEX);

            // bootloader fuse depending on bootloader location
            if (lowestBootLoader == (signature->flashSize - signature->baseBootSize))
                newBootloaderFuse = (oldBootloaderFuse & 0b11111000) | 0b110;
            else if (lowestBootLoader == (signature->flashSize - signature->baseBootSize * 2))
                newBootloaderFuse = (oldBootloaderFuse & 0b11111000) | 0b100;
            else if (lowestBootLoader == (signature->flashSize - signature->baseBootSize * 4))
                newBootloaderFuse = (oldBootloaderFuse & 0b11111000) | 0b010;
            else if (lowestBootLoader == (signature->flashSize - signature->baseBootSize * 8))
                newBootloaderFuse = (oldBootloaderFuse & 0b11111000) | 0b000;
        }

        // Can only be highFuse or extFuse due to earlier checks.
        if (signature->fuseWithBootloaderSize == highFuse)
            Debug(DEBUG_INFO, F("Changing bootloader bits (high fuse): "));
        if (signature->fuseWithBootloaderSize == extFuse)
            Debug(DEBUG_INFO, F("Changing bootloader bits (ext fuse): "));
        Debug(DEBUG_INFO, oldBootloaderFuse, BIN);
        Debug(DEBUG_INFO, F(" -> "));
        Debug(DEBUG_INFO, newBootloaderFuse, BIN);
        Debug(DEBUG_INFO, F("..."));

        // Write new fuse
        if (signature->fuseWithBootloaderSize == highFuse)
            bbprogrammer->setHighFuse(newBootloaderFuse);
        if (signature->fuseWithBootloaderSize == extFuse)
            bbprogrammer->setExtFuse(newBootloaderFuse);
        Debugln(DEBUG_INFO, F(" [OK]"));
    }
    
    // Change low fuse for external clock
    // This should be same position in low fuse for all AVR chips?
    // Please report if this is incorrect!
    Debug(DEBUG_INFO, F("Changing low fuse for external 16Mhz clock: "));
    Debug(DEBUG_INFO, fuse.low, BIN);
    Debug(DEBUG_INFO, F(" -> "));
    Debug(DEBUG_INFO, 0xff, BIN);
    Debug(DEBUG_INFO, F("..."));

    // Write new fuse
    bbprogrammer->setLowFuse(0xff);
    Debugln(DEBUG_INFO, F(" [OK]"));

    Debugln(DEBUG_INFO, F("-> Ending Programming mode."));
    bbprogrammer->stopProgramming();
    return 0x00; // No error
}
