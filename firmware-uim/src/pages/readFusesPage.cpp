#include "readFusesPage.h"

ReadFusesPage::ReadFusesPage(PageManager* manager, byte lowFuse, byte highFuse, byte extFuse, byte lockFuse, byte calibration)
    : Page( manager )
{
	this->lowFuse = lowFuse;
	this->highFuse = highFuse;
	this->extFuse = extFuse;
	this->lockFuse = lockFuse;
	this->calibration = calibration;
}

void ReadFusesPage::confirm()
{
	this->pageManager->changePage(new MainPage(this->pageManager));
}

void ReadFusesPage::initRender(SSD1306Ascii* display)
{
    display->println(F("Device Fuses:"));

    // Display Fuses
    display->print(F("Low:  0b"));
    DisplayUtils::printBin(display, this->lowFuse);
    display->println();
    display->print(F("High: 0b"));
    DisplayUtils::printBin(display, this->highFuse);
    display->println();
    display->print(F("Ext:  0b"));
    DisplayUtils::printBin(display, this->extFuse);
    display->println();
    display->print(F("Lock: 0b"));
    DisplayUtils::printBin(display, this->lockFuse);
    display->println();
    display->print(F("Cal:  0b"));
    DisplayUtils::printBin(display, this->calibration);
    display->println();
    
    // Display back button in bottom right
    const char* back = "> Back";
    display->setCursor(DISPLAY_COLUMNS - display->strWidth(back), DISPLAY_ROWS - 1);
    display->print(back);
}
