// Fake Programmer to further develope UI in firmware-UIM
// Real functionality will later be integrated to firmware-programmer

#include <Wire.h>

struct i2canswer
{
  bool busy = true;
  byte cmd;
  byte data[30];
};
i2canswer answer;

void setup() {
  Wire.begin(0x08);                // join i2c bus with address #8
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);           // start serial for output
  Serial.println("Now accepting commands...");
  answer.busy = false;
}

enum : byte
{
    cmd_ping = 0x01,
    cmd_readSignature = 0x10,
};

void loop() 
{
  if (answer.busy)
  {
    Serial.print("Received command: ");
    Serial.print(answer.cmd, HEX);

    // Clear response array
    for (int i = 0; i < 28; i++)
      answer.data[i] = 0x00;

    // PING command returns cmd_ping
    switch (answer.cmd)
    {
      case cmd_ping:
        Serial.print(" (ping dl=2000)");
        delay(2000);
        answer.data[0] = cmd_ping;
        break;
      case cmd_readSignature:
        Serial.print(" (read sig dl=4000)");
        delay(4000);
        answer.data[0] = 0x1E; //
        answer.data[1] = 0x95; // ATmega328P
        answer.data[2] = 0x0F; //
        break;
      default:
        Serial.print(" (unknown cmd)");
    }

    Serial.println(" [DONE]");
    answer.busy = false;
  }
}


void receiveEvent(int HowMany)
{
  if (HowMany != 1 || answer.busy == true)
    return;
  answer.busy = true;
  answer.cmd = Wire.read();
}

void requestEvent()
{
  Wire.write((byte *) &answer, sizeof (answer));
}
