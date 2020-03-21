#include "src/page.h"
#include "src/pageManager.h"
#include "src/pages/mainPage.h"
#include "src/pages/delayPage.h"
#include <SSD1306AsciiWire.h>

SSD1306AsciiWire display;
PageManager* ui;

void setup() {
    Serial.begin(9600);

    // Connect screen
    Serial.println(F("Welcome. STONE LABS(TM)"));
    display.begin(&Adafruit128x64, 0x3C);
    display.setFont(Adafruit5x7);

    // Setup input button
    pinMode(5, INPUT_PULLUP);
    pinMode(6, INPUT_PULLUP);
    pinMode(7, INPUT_PULLUP);

    // Setup page manager with main menu as start page
    ui = new PageManager(&display);
    ui->changePage(new DelayPage(ui, 5000, new MainPage(ui)));

    // Pin change interrupt mask for D5,6,7
    PCMSK2 = bit(PCINT21) | bit(PCINT22) | bit(PCINT23);
    PCIFR |= bit(PCIF2);    // clear any outstanding interrupts on Interrupt block 2
    PCICR |= bit(PCIE2);    // enable pin change interrupts on Interrupt block 2 (D0-7)
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

byte vector_old;
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