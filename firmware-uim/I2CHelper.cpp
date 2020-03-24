#include "I2CHelper.h"

void programmer_request(byte command)
{
    Command sendCommand;
    sendCommand.cmd = command;

    // Send no arguments by default
    for (unsigned int i = 0; i < COMMAND_DATASIZE; i++)
        sendCommand.data[i] = 0x00;
    
    // Commit request
    programmer_request(sendCommand);
}

void programmer_request(Command& command)
{
    #if DEBUG
        Serial.print(F("\n-> CMD=0x"));
        Serial.print(command.cmd, HEX);
        Serial.print(F(" DATA="));
        for (int i = 0; i < COMMAND_DATASIZE; i++)
        {
            Serial.print(F(" 0x"));
            Serial.print(command.data[i], HEX);
        }
        Serial.println();
    #endif
    // Send command to Programmer
    Wire.beginTransmission(PROGRAMMER_ADDRESS);
    Wire.write((byte*)&command, sizeof(command));
    Wire.endTransmission();
}

bool programmer_answer(Answer& value)
{
    // Request answer
    Wire.requestFrom(0x08, (int)sizeof(value));

    // Pointer to local answer
    byte* p = (byte*)&value;

    // Write received bytes to answer
    for (unsigned int i = 0; i < sizeof value; i++)
        *(p++) = Wire.read();

#if DEBUG
    Serial.print(F("<- BUSY="));
    Serial.print(value.busy, DEC);
    Serial.print(F(" CMD=0x"));
    Serial.print(value.cmd, HEX);
    Serial.print(F(" DATA="));
    for (int i = 0; i < ANSWER_DATASIZE; i++)
    {
        Serial.print(" 0x");
        Serial.print(value.data[i], HEX);
    }
    Serial.print(F(" ERR=0x"));
    Serial.print(value.error, HEX);
    Serial.println();
#endif

    // Dont spam the programmer with requests
    if (value.busy)
        delay(ACTIVE_POLL_DELAY_MS);

    // Return true if answer is ready => not busy
    return !value.busy;
}

void programmer_requestanswer(byte command, Answer& value)
{
    programmer_request(command);
    while (!programmer_answer(value)) {}
}
