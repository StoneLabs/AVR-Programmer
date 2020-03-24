#define XSTR(s) STR(s)
#define STR(s) #s

#define __PVERSION__ "v-1.0"

#include "src/page.h"
#include "src/pageManager.h"
#include "src/pages/bootPage.h"
#include "I2CHelper.h"

#include <SSD1306AsciiWire.h>
#include <Wire.h>

SSD1306AsciiWire display;
PageManager* ui;

void setup() {
    Serial.begin(115200);
    while (!Serial) {};
    
    // Connect screen
    Serial.println(F("\n\nStone Labs. Smart ISP"));
    Serial.println(F("SmartISP - User Interface Module"));
    Serial.println(F("Verion " XSTR(__PVERSION__) " compiled at " __DATE__ " " __TIME__ " using Arduino IDE version " XSTR(ARDUINO)  " Debug level " XSTR(DEBUG)));

    display.begin(&Adafruit128x64, 0x3C);
    display.setFont(Adafruit5x7);
    
    // Setup input button
    pinMode(5, INPUT_PULLUP);
    pinMode(6, INPUT_PULLUP);
    pinMode(7, INPUT_PULLUP);

    // Pin change interrupt mask for D5,6,7
    PCMSK2 = bit(PCINT21) | bit(PCINT22) | bit(PCINT23);
    PCIFR |= bit(PCIF2);    // clear any outstanding interrupts on Interrupt block 2
    PCICR |= bit(PCIE2);    // enable pin change interrupts on Interrupt block 2 (D0-7)

    // Setup page manager with boot page as start page.
    // Minimum welcome screen duration 3 seconds.
    ui = new PageManager(&display);
    ui->changePage(new BootPage(ui, 3000));
}

bool press5 = false, press6 = false, press7 = false;
void loop()
{
    ui->updatePage();
    if (press5) 
    { 
        ui->left();
        press5 = false; 
    }
    if (press6) 
    {
        ui->right();
        press6 = false; 
    }
    if (press7) 
    {
        ui->confirm();
        press7 = false; 
    }
}

byte vector_old = 0xFF;
ISR(PCINT2_vect)
{
    // Check for bitchange 0->1 on D7
    if (((vector_old ^ PIND) & bit(PIND7)) && !(PIND & bit(PIND7)))
        press7 = true;
    // Check for bitchange 0->1 on D6
    if (((vector_old ^ PIND) & bit(PIND6)) && !(PIND & bit(PIND6)))
        press6 = true;
    // Check for bitchange 0->1 on D5
    if (((vector_old ^ PIND) & bit(PIND5)) && !(PIND & bit(PIND5)))
        press5 = true;

    vector_old = PIND;
}