#define XSTR(s) STR(s)
#define STR(s) #s

#define NUMITEMS(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0])))
#define __PVERSION__ "pre-0.01"
#define DEBUG 0

#include "src/programmer/bbprogrammer.h"
#include "src/programmer/signatues.h"

#define P_SCK 13
#define P_MISO 12
#define P_MOSI 11
#define P_RESET 10

void setup()
{
    Serial.begin(9600);
    while (!Serial) {}

    Serial.println("\n\nStone Labs. Smart ISP");
    Serial.println("Verion " XSTR(__PVERSION__) " compiled at " __DATE__ " " __TIME__ " using Arduino IDE version " XSTR(ARDUINO));

    Serial.println("\nEnter 'G' to start.");
    while (Serial.read() != 'G');

    Serial.println("\n-> Starting 8 Mhz Clock on Pin 9.");
    // setup high freq PWM on pin 9 (timer 1)
    // 50% duty cycle -> 8 MHz
    OCR1A = 0;
    ICR1 = 1;
    // OC1A output, fast PWM
    TCCR1A = _BV(WGM11) | _BV(COM1A1);
    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10); // no clock prescale

    using namespace programmer;

    Serial.println("\n-> Entering Programming mode.");
    BBProgrammer programmer = BBProgrammer(P_SCK, P_MOSI, P_MISO, P_RESET);
    if (!programmer.startProgramming(5))
        return;

    
    delay(1000);
    Serial.println("\n-> Reading Signature.");
    byte signature[] = { 0x00, 0x00, 0x00 };
    programmer.readSignature(signature);
    Serial.print("Read signature: ");
    Serial.print(signature[0], HEX);
    Serial.print(signature[1], HEX);
    Serial.println(signature[2], HEX);

    bool knownSignature = false;
    signatureType currentSignature;
    for (byte j = 0; j < NUMITEMS(signatures); j++)
    {
        // Copy from PROGMEM to Memory
        memcpy_P(&currentSignature, &signatures[j], sizeof currentSignature);
        if (memcmp(signature, currentSignature.sig, sizeof signature) == 0)
        {
            knownSignature = true;
            Serial.print("Processor = ");
            Serial.println(currentSignature.desc);
            Serial.print("Flash memory size = ");
            Serial.print(currentSignature.flashSize, DEC);
            Serial.println(" bytes.");
            return;
        }  // end of signature found
    }  // end of for each signature
    if (!knownSignature)
        Serial.println("Unrecogized signature.");


    delay(1000);
    Serial.println("\n-> Leaving Programming mode.");
    programmer.stopProgramming();
}

void loop() 
{
  
}
