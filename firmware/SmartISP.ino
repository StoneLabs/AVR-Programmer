#define XSTR(s) STR(s)
#define STR(s) #s

#define __PVERSION__ "pre-0.01"
#define DEBUG 0

#include "src/programmer/bbprogrammer.h"

#define P_SCK 7
#define P_MISO 6
#define P_MOSI 5
#define P_RESET 4

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
    if (programmer.readSignature())
        printSignature(programmer.getSignature());

    delay(1000);
    Serial.print("\n-> Erasing CHIP.");
    programmer.erase();
    Serial.println(" [OK]");

    delay(1000);
    Serial.println("\n-> Leaving Programming mode.");
    programmer.stopProgramming();
}

void printSignature(Signature* signature)
{
    Serial.print("Processor = ");
    Serial.println(signature->desc);
    Serial.print("Flash memory size = ");
    Serial.print(signature->flashSize, DEC);
    Serial.println(" bytes.");
}

void loop() 
{
  
}

