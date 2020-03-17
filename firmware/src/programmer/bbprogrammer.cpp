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
        Serial.print("Attempting to enter programming mode ...");

        if (this->isProgramming)
        {
            Serial.print("Error: Allready in programming mode.");
            return false;
        }
        
        unsigned int timeout = 0;
#if DEBUG > 0
        byte answer1;
        byte answer2;
        byte answer3;
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
#if DEBUG > 0
            answer1 = this->spi->transfer(progamEnable);
            answer2 = this->spi->transfer(programAcknowledge);
            answer  = this->spi->transfer(0x1);
            answer4 = this->spi->transfer(0x2);
#else
            this->spi->transfer(progamEnable);
            this->spi->transfer(programAcknowledge);
            answer = this->spi->transfer(0x1);
            this->spi->transfer(0x2);
#endif
            interrupts();

            /// Debug
#if DEBUG > 0
            Serial.print("\nSPI write: 0x"); Serial.print(progamEnable, HEX);
            Serial.print(" 0x"); Serial.print(programAcknowledge, HEX);
            Serial.print(" 0x"); Serial.print(0x1, HEX);
            Serial.print(" 0x"); Serial.println(0x2, HEX);
            Serial.print("SPI read: 0x"); Serial.print(answer1, HEX);
            Serial.print(" 0x"); Serial.print(answer2, HEX);
            Serial.print(" 0x"); Serial.print(answer, HEX);
            Serial.print(" 0x"); Serial.println(answer4, HEX);
#endif

            delay(1000);

            // Target confirmes received programming enabable instructure.
            // This does however not mean that is has accepted it?
            // We will however assume it did :D
            if (answer != programAcknowledge)
            {
                Serial.print(".");
                if (++timeout >= tries)
                {
                    Serial.println(" [FAILED]");
                    this->isProgramming = false;
                    return false;
                }
            }
        } while (answer != programAcknowledge);

        Serial.println(" [OK]");
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

            Serial.println("Programming mode ended.");
        }
        else
            Serial.println("Programming mode allready ended.");
    }

    byte BBProgrammer::execCommand(byte b1, byte b2, byte b3, byte b4)
    {
        noInterrupts();
        this->spi->transfer(b1);
        this->spi->transfer(b2);
        this->spi->transfer(b3);
        byte answer = this->spi->transfer(b4);
        interrupts();

        return answer;
    }

    void BBProgrammer::readSignature(byte(&signature)[3])
    {
        for (byte i = 0; i < 3; i++)
            signature[i] = execCommand(readSignatureByte, 0, i);
    }
}