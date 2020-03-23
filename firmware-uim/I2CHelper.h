#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Wire.h>

#define PROGRAMMER_ADDRESS 0x08
#define PROGRAMMER_DATASIZE 30
#define DEBUG true

typedef struct {
    bool busy;
    byte cmd;
    byte data[30];
} Answer;

enum : byte
{
    // Meta operations
    cmd_ping = 0x01,

    // Read operations
    cmd_readSignature = 0x10,

    // Write operations
    cmd_erase = 0x20,
};

void programmer_request(byte command);
bool programmer_answer(Answer& value);

void programmer_requestanswer(byte command, Answer& value);