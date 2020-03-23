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

byte hexton(byte h)
{
    // Convert ascii HEX to number
    if (h >= '0' && h <= '9')
        return(h - '0');
    if (h >= 'A' && h <= 'F')
        return((h - 'A') + 10);

    HaltError(F("Invalid HEX number."));
}
byte twos_complement(byte val)
{
    return -(unsigned int)val;
}

// Returns lowest address behind current page. (so min addr >= pageaddr + pagesize) 
// More information on HEX file: https://en.wikipedia.org/wiki/Intel_HEX
unsigned long readImagePage(SdFile* file, const unsigned long flashsize, const unsigned long pageaddr, const unsigned long pagesize, byte* pagebuffer)
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
                HaltError(F("Invalid hex file (1)"));

            // Read line `metadata`
            l_bytecount = hexton(lineBuffer[1]) << 4 | hexton(lineBuffer[2]);
            l_address = hexton(lineBuffer[3]) << 12;
            l_address = l_address | hexton(lineBuffer[4]) << 8;
            l_address = l_address | hexton(lineBuffer[5]) << 4;
            l_address = l_address | hexton(lineBuffer[6]) << 0;
            l_recordtype = hexton(lineBuffer[7]) << 4 | hexton(lineBuffer[8]);

            if (l_bytecount > HEX_MAX_DATALEN)
                HaltError(F("HEX Data too long to process"));

            l_checksum = hexton(lineBuffer[9 + l_bytecount * 2]) << 4 | hexton(lineBuffer[10 + l_bytecount * 2]);

            if (l_bytecount > HEX_MAX_DATALEN)
                HaltError(F("HEX Data too long to process"));

            if (l_recordtype < 0 || l_recordtype > 3)
                HaltError(F("Unsupported HEX entry."));

            if (l_recordtype == 3)
                Debugln(DEBUG_VERBOSE, F("HEX contains 'Start Segment Address'. Entry will be ignored."));

            // Checksum check
            byte calcCheckSum = 0x00;
            for (byte i = 1; i < 9 + l_bytecount * 2; i += 2) // From 1 to last databyte
                calcCheckSum += hexton(lineBuffer[i + 0]) << 4 |
                hexton(lineBuffer[i + 1]);

            if (twos_complement(calcCheckSum) != l_checksum)
                HaltError(F("Line checksum mismatch!"));

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
                    HaltError(F("HEX not in flash bounds!"));

                // Page adding
                for (byte i = 9; i < 9 + l_bytecount * 2; i += 2) // From first to last databyte
                {
                    // Write to page buffer if address is in current `page area`
                    if (l_address >= pageaddr && l_address - pageaddr < pagesize)
                    {
                        pagebuffer[l_address - pageaddr] =
                            hexton(lineBuffer[i + 0]) << 4 | hexton(lineBuffer[i + 1]);

                        Debug(DEBUG_VERBOSE, F("Writing to paging buffer: "));
                        Debug(DEBUG_VERBOSE, hexton(lineBuffer[i + 0]) << 4 | hexton(lineBuffer[i + 1]), HEX);
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
            lineBuffer[index] = charBuffer; // Write character to lineBuffer

        index++;
    }

    // Clean up
    delete[] lineBuffer;

    return smallestAfter;
}