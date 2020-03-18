#define XSTR(s) STR(s)
#define STR(s) #s

#define __PVERSION__ "pre-0.01"
#define DEBUG false

#include "src/programmer/bbprogrammer.h"

#define P_SCK 7
#define P_MISO 6
#define P_MOSI 5
#define P_RESET 4

void printFuses(const programmer::BBProgrammer::Fuse& fuse)
{
    Serial.print("Low fuse: ");
    Serial.print(fuse.low, HEX);
    Serial.print(" = ");
    Serial.println(fuse.low, BIN);

    Serial.print("High fuse: ");
    Serial.print(fuse.high, HEX);
    Serial.print(" = ");
    Serial.println(fuse.high, BIN);

    Serial.print("Extended fuse: ");
    Serial.print(fuse.extended, HEX);
    Serial.print(" = ");
    Serial.println(fuse.extended, BIN);

    Serial.print("Lock Byte: ");
    Serial.print(fuse.lock, HEX);
    Serial.print(" = ");
    Serial.println(fuse.lock, BIN);

    Serial.print("Calibration byte: ");
    Serial.print(fuse.calibration, HEX);
    Serial.print(" = ");
    Serial.println(fuse.calibration, BIN);
}

void printSignature(const Signature* signature)
{
    Serial.print("Processor = ");
    Serial.println(signature->desc);
    Serial.print("Flash memory size = ");
    Serial.print(signature->flashSize, DEC);
    Serial.println(" bytes.");
}

void setup()
{
    Serial.begin(9600);
    while (!Serial) {}

    Serial.println("\n\nStone Labs. Smart ISP");
    Serial.println("Verion " XSTR(__PVERSION__) " compiled at " __DATE__ " " __TIME__ " using Arduino IDE version " XSTR(ARDUINO));

    Serial.println("\nEnter 'G' to start.");
    while (Serial.read() != 'G');

    Serial.println("\n-> Starting 8 Mhz Clock on Pin 9.");

    // set up 8 MHz timer on PIN 10 (OC1B)
    // https://arduino.stackexchange.com/questions/16698/arduino-constant-clock-output
    pinMode(10, OUTPUT);
    // set up Timer 1
    TCCR1A = bit(COM1B0);  // toggle OC1B on Compare Match
    TCCR1B = bit(WGM12) | bit(CS10);   // CTC, no prescaling
    OCR1B = 0;       // output every cycle

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
    Serial.print("\n-> Reading Fuses.");
    programmer.readFuses();
    Serial.println(" [OK]");
    const BBProgrammer::Fuse& fuse = programmer.getFuses();
    printFuses(fuse);


    delay(1000);
    Serial.println("\n-> Leaving Programming mode.");
    programmer.stopProgramming();
}

void loop() 
{
  
}

