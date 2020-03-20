#include "bbprogrammer.h"

namespace programmer
{
    BBProgrammer::BBProgrammer(byte p_sck, byte p_mosi, byte p_miso, byte p_reset)
    {
        // Setup software SPI
        this->spi = new SoftwareSPI(p_sck, p_mosi, p_miso, p_reset);
        this->spi->begin();

        // Reset target chip!
        this->spi->select();
    }

    BBProgrammer::~BBProgrammer()
    {
        if (this->isProgramming)
            stopProgramming();
        delete this->spi;
    }

    // http://ww1.microchip.com/downloads/en/appnotes/atmel-0943-in-system-programming_applicationnote_avr910.pdf
    bool BBProgrammer::startProgramming(unsigned int tries)
    {
        Debug(DEBUG_INFO, F("Attempting to enter programming mode ..."));

        if (this->isProgramming)
        {
            Debug(DEBUG_INFO, F(" allready in programming mode."));
            return false;
        }
        
        unsigned int timeout = 0;
#if DEBUG >= DEBUG_ALL
        byte answer1;
        byte answer2;
        byte answer4;
#endif
        byte answer;
        
        // give it some time?
        delay(100);

        // we are in sync if we get back programAcknowledge on the third byte
        do
        {
            // Pulse reset according to datasheet
            noInterrupts();
            this->spi->deselect();
            delayMicroseconds(10);  // pulse for at least 2 clock cycles
            this->spi->select();
            interrupts();

            delay(25);  // wait at least 20 ms

            // Enter programming mode
            noInterrupts();
#if DEBUG >= DEBUG_ALL
            answer1 = this->spi->transfer(programEnable);
            answer2 = this->spi->transfer(programAcknowledge);
            answer  = this->spi->transfer(0x1);
            answer4 = this->spi->transfer(0x2);
#else
            this->spi->transfer(programEnable);
            this->spi->transfer(programAcknowledge);
            answer = this->spi->transfer(0x1);
            this->spi->transfer(0x2);
#endif
            interrupts();

            // Debug
#if DEBUG >= DEBUG_ALL
            Debug(DEBUG_ALL, F("\nSPI write: 0x")); Debug(DEBUG_ALL, programEnable, HEX);
            Debug(DEBUG_ALL, F(" 0x")); Debug(DEBUG_ALL, programAcknowledge, HEX);
            Debug(DEBUG_ALL, F(" 0x")); Debug(DEBUG_ALL, 0x1, HEX);
            Debug(DEBUG_ALL, F(" 0x")); Debugln(DEBUG_ALL, 0x2, HEX);

            Debug(DEBUG_ALL, F("SPI read: 0x")); Debug(DEBUG_ALL, answer1, HEX);
            Debug(DEBUG_ALL, F(" 0x")); Debug(DEBUG_ALL, answer2, HEX);
            Debug(DEBUG_ALL, F(" 0x")); Debug(DEBUG_ALL, answer, HEX);
            Debug(DEBUG_ALL, F(" 0x")); Debugln(DEBUG_ALL, answer4, HEX);
#endif

            delay(1000);

            // Target confirmes received programming enabable instructure.
            // This does however not mean that is has accepted it?
            // We will however assume it did :D
            if (answer != programAcknowledge)
            {
                Debug(DEBUG_INFO, F("."));
                if (++timeout >= tries)
                {
                    Debug(DEBUG_INFO, F(" [FAILED]"));
                    this->isProgramming = false;
                    return false;
                }
            }
        } while (answer != programAcknowledge);

        Debug(DEBUG_INFO, F(" [OK]"));
        this->isProgramming = true;
        return true;
    }

    void BBProgrammer::stopProgramming()
    {
        if (this->isProgramming)
        {
            // Disable reset and set all pins to internal pull-up
            this->spi->end();
            this->isProgramming = false;

            Debugln(DEBUG_INFO, F("Programming mode ended."));
        }
        else
            Debugln(DEBUG_INFO, F("Programming mode allready ended."));
    }

    byte BBProgrammer::execCommand(byte b1, byte b2, byte b3, byte b4)
    {
#if DEBUG >= DEBUG_ALL
        noInterrupts();
        byte answer1 = this->spi->transfer(b1);
        byte answer2 = this->spi->transfer(b2);
        byte answer3 = this->spi->transfer(b3);
        byte answer = this->spi->transfer(b4);
        interrupts();

        Debug(DEBUG_ALL, F("\nSPI write: 0x")); Debug(DEBUG_ALL, b1, HEX);
        Debug(DEBUG_ALL, F(" 0x")); Debug(DEBUG_ALL, b2, HEX);
        Debug(DEBUG_ALL, F(" 0x")); Debug(DEBUG_ALL, b3, HEX);
        Debug(DEBUG_ALL, F(" 0x")); Debugln(DEBUG_ALL, b4, HEX);

        Debug(DEBUG_ALL, F("SPI read: 0x")); Debug(DEBUG_ALL, answer1, HEX);
        Debug(DEBUG_ALL, F(" 0x")); Debug(DEBUG_ALL, answer2, HEX);
        Debug(DEBUG_ALL, F(" 0x")); Debug(DEBUG_ALL, answer3, HEX);
        Debug(DEBUG_ALL, F(" 0x")); Debugln(DEBUG_ALL, answer, HEX);
#else
        noInterrupts();
        this->spi->transfer(b1);
        this->spi->transfer(b2);
        this->spi->transfer(b3);
        byte answer = this->spi->transfer(b4);
        interrupts();
#endif
        
        return answer;
    }

    bool BBProgrammer::readSignature()
    {
        if (!this->isProgramming)
            HaltError(F("Error: Not in programming mode."));

        byte signature[] = { 0x00, 0x00, 0x00 };

        for (byte i = 0; i < 3; i++)
            signature[i] = execCommand(readSignatureByte, 0, i);


        if (signature[0] == 0x00)
        {
            // Lock byte should be set. Erase must be isued!
            Debugln(DEBUG_INFO, F("Device ID reads 0x00. Lock could be set."));
        }
        else
        {
            delete this->signature;
            Signature* currentSignature = new Signature();
            for (byte j = 0; j < NUMITEMS(signatures); j++)
            {
                // Copy from PROGMEM to Memory
                memcpy_P(currentSignature, &signatures[j], sizeof *currentSignature);
                if (memcmp(signature, currentSignature->sig, sizeof signature) == 0)
                {
                    // Signature found and known
                    this->signature = currentSignature;
                    return true;
                }
            } 
            
            HaltError(F("Error: Unrecogized signature. Chip is not supported by this program."));
        }

        return false;
    }

    const Signature* BBProgrammer::getSignature() const
    {
        return this->signature;
    }

    void BBProgrammer::readFuses()
    {
        if (!this->isProgramming)
            HaltError(F("Error: Not in programming mode."));

        this->fuses.low = execCommand(readLowFuseByte, readLowFuseByteArg2);
        this->fuses.high = execCommand(readHighFuseByte, readHighFuseByteArg2);
        this->fuses.extended = execCommand(readExtendedFuseByte, readExtendedFuseByteArg2);
        this->fuses.lock = execCommand(readLockByte, readLockByteArg2);
        this->fuses.calibration= execCommand(readCalibrationByte);

        // Testing
        //Serial.println("Writing low to FF! (TMP)");
        //execCommand(programEnable, writeLowFuseByte, 0, 0xFF);
    }
    void BBProgrammer::pollUntilReady()
    {         
        // wait till ready
        while ((execCommand(pollReady) & 1) == 1) {}
    }

    const BBProgrammer::Fuse& BBProgrammer::getFuses() const
    {
        return this->fuses;
    }

    void BBProgrammer::setHighFuse(const byte fuse)
    {
#if SAFETY_CHECKS
        // Check if signature has been read.
        if (this->signature == nullptr)
            HaltError(F("Attempting to write high fuse without signature!"));

        // Confirm with safety mask
        if ((fuse & signature->safetyMaskOne) != signature->safetyMaskOne ||
            (fuse & signature->safetyMaskZero) != 0)
        {
            HaltError(F("WARNING: ILLEGAL FUSE CONFIGURATION. ABORTING EXECUTION."));
            
            // Just for safety so a broken HaltError doesn't
            // lead to bricked chips!
            while (true) {}; 
        }

        execCommand(programEnable, writeHighFuseByte, 0x00, fuse);
        pollUntilReady();
#endif
    }

    void BBProgrammer::setLowFuse(const byte fuse)
    {
        execCommand(programEnable, writeLowFuseByte, 0x00, fuse);
        pollUntilReady();
    }

    void BBProgrammer::flashPage(unsigned long pageaddr, byte* pagebuffer)
    {
        // Check if signature has been read.
        if (this->signature == nullptr)
            HaltError(F("Attempting to flash page without signature!"));
        
        for (unsigned long addr = 0; addr < this->signature->pageSize / 2; addr++)
        {
            byte lowAddr = addr & 0xFFUL;
            byte highAddr = (addr & 0xFF00UL) >> 8;
            
            execCommand(loadProgramMemoryPageLow, highAddr, lowAddr, pagebuffer[addr * 2]);
            execCommand(loadProgramMemoryPageHigh, highAddr, lowAddr, pagebuffer[addr * 2 + 1]);
        }

        // Commiting the page buffer to the flash 
        // with 'writeProgramMemoryPage' is done in 
        // word addressing. (e.g. page 0x0080-0x00FF would
        // be committed with $4C 00 40 00.
        unsigned long pageWordAddr = pageaddr / 2;
        byte pageWordAddrLow = pageWordAddr & 0xFFUL;
        byte pageWordAddrHigh = (pageWordAddr & 0xFF00UL) >> 8;

        execCommand(writeProgramMemoryPage, pageWordAddrHigh, pageWordAddrLow, 0x00);
        pollUntilReady();
    }

    void BBProgrammer::erase()
    {
        if (!this->isProgramming)
            HaltError(F("Error: Not in programming mode."));

        execCommand(programEnable, chipErase);
        this->pollUntilReady();
    }
}