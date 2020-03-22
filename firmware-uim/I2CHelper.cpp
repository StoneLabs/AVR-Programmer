#include "I2CHelper.h"

void programmer_request(byte command)
{
    // Send command to Programmer
    Wire.beginTransmission(PROGRAMMER_ADDRESS);
    Wire.write(command);
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

    // Return true if answer is ready => not busy
    return !value.busy;
}

void programmer_requestanswer(byte command, Answer& value)
{
    programmer_request(command);
    while (!programmer_answer(value)) {}
}
