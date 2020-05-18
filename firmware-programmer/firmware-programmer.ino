#define XSTR(s) STR(s)
#define STR(s) #s

#define __PVERSION__ "v-1.2"

// External Dependencies
#include <SPI.h>
#include <SdFat.h>
#include <Wire.h>

// Debug level can be changed in debug.h
#include "src/debug.h"
#include "src/programmer/bbprogrammer.h"
#include "i2c_enums.h"
#include "helper.h"

#define P_SCK 7
#define P_MISO 6
#define P_MOSI 5
#define P_RESET 4

using namespace programmer;

#define SFN_LENGTH 13

typedef struct {
    byte cmd;
    byte data[31];
} Command;
typedef struct {
    bool busy;
    byte cmd;
    byte data[29];
    byte error;
} Answer;


// Global variables
Command command;
Answer answer;
SdFat sd;
SdFile file;

BBProgrammer* bbprogrammer = nullptr;

void setup() {
    Serial.begin(115200);
    while (!Serial) {}

    Debugln(DEBUG_INFO, F("\n\nStone Labs. Smart ISP"));
    Debugln(DEBUG_INFO, F("SmartISP - Programmer Module"));
    Debugln(DEBUG_INFO, F("Verion " XSTR(__PVERSION__) " compiled at " __DATE__ " " __TIME__ " using Arduino IDE version " XSTR(ARDUINO)  " Debug level " XSTR(DEBUG)));

    Debugln(DEBUG_INFO, F("\n-> Starting I2C slave mode."));
    Wire.begin(0x08);                // join i2c bus with address #8
    Wire.onRequest(requestEvent);
    Wire.onReceive(receiveEvent);

    Debugln(DEBUG_INFO, F("\n-> Starting 8 Mhz Clock on Pin 9."));

    // set up 8 MHz timer on PIN 10 (OC1B)
    // https://arduino.stackexchange.com/questions/16698/arduino-constant-clock-output
    pinMode(10, OUTPUT);
    // set up Timer 1
    TCCR1A = bit(COM1B0);  // toggle OC1B on Compare Match
    TCCR1B = bit(WGM12) | bit(CS10);   // CTC, no prescaling
    OCR1B = 0;       // output every cycle

    Debug(DEBUG_INFO, F("\n-> Initializing SD card..."));
    sd.begin(3, SPI_HALF_SPEED); // We dont need an SD card to start
    //if (!sd.begin(3, SPI_HALF_SPEED))
    //    sd.initErrorHalt();

    Debugln(DEBUG_INFO, F(" [OK]"));

    // List all files in root directory.
    // The volume working directory, vwd, is root.
#if DEBUG >= DEBUG_INFO
    while (file.openNext(sd.vwd(), O_READ))
    {
        Debug(DEBUG_INFO, F("|-- "));
        file.printName(&Serial);
        Debug(DEBUG_INFO, F(" "));
        file.printModifyDateTime(&Serial);
        Debugln(DEBUG_INFO, F(""));
        file.close();
    }
    sd.vwd()->rewind();
#endif
    
    Debugln(DEBUG_INFO, F("\n-> Initializing Programmer."));
    bbprogrammer = new BBProgrammer(P_SCK, P_MOSI, P_MISO, P_RESET);

    Debugln(DEBUG_INFO, F("\n-> Now accepting commands."));
    answer.busy = false;
    pinMode(2, OUTPUT);
}

void answerError(byte error)
{
    answer.error = error;
    answer.busy = false;
    Debug(DEBUG_INFO, F("-> Command failed with error: "));
    Debugln(DEBUG_INFO, error, HEX);
}

void loop()
{
    if (answer.busy)
    {
        Serial.print("\n==> Received command: ");
        Serial.println(answer.cmd, HEX);

        // PING command returns cmd_ping
        switch (answer.cmd)
        {
        case cmd_ping:
            {
                Debugln(DEBUG_INFO, F("-> Responsing to ping."));
                answer.data[0] = cmd_ping;
            }
            break;
        case cmd_readSignature:
            {
                // Read signature bytes
                Debugln(DEBUG_INFO, F("-> Entering Programming mode."));
                if (!bbprogrammer->startProgramming(5))
                {
                    answerError(error_programmingMode);
                    return;
                }
                Debugln(DEBUG_INFO, F("-> Reading signature byte."));
                bbprogrammer->readSignatureBytes(answer.data[0], answer.data[1], answer.data[2]);
                Debugln(DEBUG_INFO, F("-> Ending Programming mode."));
                bbprogrammer->stopProgramming();
            }
            break;
        case cmd_erase:
            {
                // Erase Chip signature
                Debugln(DEBUG_INFO, F("-> Entering Programming mode."));
                if (!bbprogrammer->startProgramming(5))
                {
                    answerError(error_programmingMode);
                    return;
                }
                Debugln(DEBUG_INFO, F("-> Erasing chip."));
                bbprogrammer->erase();
                Debugln(DEBUG_INFO, F("-> Ending Programming mode."));
                bbprogrammer->stopProgramming();
            }
            break;
        case cmd_readFuses:
            {
                // Read fuse bytes
                Debugln(DEBUG_INFO, F("-> Entering Programming mode."));
                if (!bbprogrammer->startProgramming(5))
                {
                    answerError(error_programmingMode);
                    return;
                }

                Debugln(DEBUG_INFO, F("-> Reading Fuses."));
                bbprogrammer->readFuses();
                printFuses(bbprogrammer->getFuses());

                // Answer with fuse bytes
                answer.data[lowFuse] = bbprogrammer->getFuses().low;
                answer.data[highFuse] = bbprogrammer->getFuses().high;
                answer.data[extFuse] = bbprogrammer->getFuses().extended;
                answer.data[lockFuse] = bbprogrammer->getFuses().lock;
                answer.data[calibrationFuse] = bbprogrammer->getFuses().calibration;

                Debugln(DEBUG_INFO, F("-> Ending Programming mode."));
                bbprogrammer->stopProgramming();
            }
            break;
        case cmd_openNextFile:
            { // Explicit block for case variable foundFile and file_sfn
                Debugln(DEBUG_INFO, F("-> Opening next file"));

                bool foundFile = false;
                while (file.openNext(sd.vwd(), O_READ))
                {
                    foundFile = true;

                    Debugln(DEBUG_INFO, F("Opened file."));
                    Debug(DEBUG_INFO, F("Name: "));
#if DEBUG >= DEBUG_INFO
                    file.printName(&Serial);
#endif
                    Debug(DEBUG_INFO, F(" SFN: "));
#if DEBUG >= DEBUG_INFO
                    file.printSFN(&Serial);
#endif

                    // Copy SFN in tmp buffer
                    char file_sfn[SFN_LENGTH];
                    file.getSFN(file_sfn); // 13. char is 0x00

                    // Get length and compare last 4 bytes with .HEX or .hex
                    byte file_sfn_length = strlen(file_sfn);
                    if (file_sfn_length > 4 &&
                        (strcmp(file_sfn + file_sfn_length - 4, ".hex") == 0 ||
                            strcmp(file_sfn + file_sfn_length - 4, ".HEX") == 0))
                    {
                        // Files is .hex => copy tmp buffer to answer buffer
                        Debugln(DEBUG_INFO, F(" [OK: .HEX]"));
                        memcpy(answer.data, file_sfn, SFN_LENGTH);

                        file.close();
                        break;
                    }
                    else
                    {
                        // Files is not .hex => open next file via while
                        Debugln(DEBUG_INFO, F(" [IGNORE]"));
                        file.close();
                        continue;
                    }
                }
                if (!foundFile)
                {
                    // Not a single file was found
                    //  Rewind working directory and return
                    //  empty buffer.
                    sd.vwd()->rewind();
                    Debugln(DEBUG_INFO, F("No file found. Rewinding."));
                }
            }
            break;
        case cmd_flashFile:
            {
                Debug(DEBUG_INFO, F("\n-> Flashing HEX source /"));
                Debugln(DEBUG_INFO, (char*)command.data);
                if (!file.open((char*)command.data, O_READ))
                {
                    answerError(error_openFile);
                    return;
                }

                // Flash file. Will not be closed by flashFile()
                byte status = flashFile(&file, bbprogrammer);
                file.close();

                if (status > 0x00)
                {
                    answerError(status);
                    return;
                }
            }
            break;
        case cmd_writeLowFuse:
            [[fallthrough]];
        case cmd_writeHighFuse:
            [[fallthrough]];
        case cmd_writeExtFuse:
            [[fallthrough]];
        case cmd_writeLockFuse:
            {
                if (command.data[0] != command.data[1])
                {
                    answerError(error_fuseCheckMismatch);
                    return;
                }
                // Read signature bytes
                Debugln(DEBUG_INFO, F("-> Entering Programming mode."));
                if (!bbprogrammer->startProgramming(5))
                {
                    answerError(error_programmingMode);
                    return;
                }
                if (!bbprogrammer->readSignature())
                {
                    answerError(error_fuseWithoutSignature);
                    return;
                }
                switch (command.cmd)
                {
                case cmd_writeLowFuse:
                    Debug(DEBUG_INFO, F("-> Writing low fuse to:"));
                    Debugln(DEBUG_INFO, command.data[0], BIN);
                    bbprogrammer->setLowFuse(command.data[0]);
                    break;
                case cmd_writeHighFuse:
                    Debug(DEBUG_INFO, F("-> Writing high fuse."));
                    Debugln(DEBUG_INFO, command.data[0], BIN);
                    if (!bbprogrammer->setHighFuse(command.data[0]))
                    {
                        bbprogrammer->stopProgramming();
                        answerError(error_refusedByProgrammer);
                        return;
                    }
                    break;
                case cmd_writeExtFuse:
                    Debug(DEBUG_INFO, F("-> Writing ext. fuse."));
                    Debugln(DEBUG_INFO, command.data[0], BIN);
                    bbprogrammer->setExtFuse(command.data[0]);
                    break;
                case cmd_writeLockFuse:
                    Debug(DEBUG_INFO, F("-> Writing lock bits."));
                    Debugln(DEBUG_INFO, command.data[0], BIN);
                    bbprogrammer->setLockBits(command.data[0]);
                    break;
                }
                Debugln(DEBUG_INFO, F("-> Ending Programming mode."));
                bbprogrammer->stopProgramming();
            }
            break;
        default:
            answerError(error_unknownCommand);
            return;
        }

        Debugln(DEBUG_INFO, F("-> Command finished."));
        answer.busy = false;
    }
}

// Interrupt handler
void receiveEvent(int HowMany)
{
    if (HowMany != sizeof(command) || answer.busy == true)
        return;

    // Read incoming bytes to command
    // Clearing command argument buffer is not needed
    // as it will be overwritten anyway.
    byte* p = (byte*)&command;
    for (unsigned int i = 0; i < sizeof command; i++)
        *(p++) = Wire.read();

    // Clear error byte and busy bit
    answer.busy = true;
    answer.error = 0x00;

    // Set response command to incoming command
    answer.cmd = command.cmd;

    // Clear response array
    for (int i = 0; i < 28; i++)
        answer.data[i] = 0x00;
}

void requestEvent()
{
    Wire.write((byte*)&answer, sizeof(answer));
}