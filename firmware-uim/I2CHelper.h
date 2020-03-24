#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Wire.h>

#define PROGRAMMER_ADDRESS 0x08
#define COMMAND_DATASIZE 31
#define ANSWER_DATASIZE 29

#define ACTIVE_POLL_DELAY_MS 50
#define DEBUG true

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

enum
{
    lowFuse = 0,
    highFuse = 1,
    extFuse = 2,
    lockFuse = 3,
    calibrationFuse = 4,
};

#define SFN_LENGTH 13
enum : byte
{
    //// Meta operations
    cmd_ping = 0x01,

    // Open next file return data looks as follows:
    // data[0] = bool fileFound? // false means rewind is needed, last file
    // data[1-28] = char[] SFN
    // will cycle around if end is reached
    cmd_openNextFile = 0x02,

    //// Read operations
    cmd_readSignature = 0x10,
    cmd_readFuses = 0x11,

    //// Write operations
    cmd_erase = 0x20,
    cmd_flashFile = 0x21,
};

void programmer_request(byte command);
void programmer_request(Command& command);
bool programmer_answer(Answer& value);

void programmer_requestanswer(byte command, Answer& value);