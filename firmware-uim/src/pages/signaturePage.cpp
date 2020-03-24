#include "signaturePage.h"

SignaturePage::SignaturePage(PageManager* manager, byte b1, byte b2, byte b3)
	: Page( manager )
{
    this->b1 = b1;
    this->b2 = b2;
    this->b3 = b3;
}

void SignaturePage::init()
{
    if (this->b1 == 0x00)
    {
        // Device locked
        // Abort current page init -> no rendering
        // and change to LockedDevicePage
        this->pageManager->changePage(new LockedDevicePage(this->pageManager, b1, b2, b3));
        this->pageManager->cancelPage();
        return;
    }
    for (byte j = 0; j < NUMITEMS(signatures); j++)
    {
        // Copy from PROGMEM to Memory
        memcpy_P(&this->signature, &signatures[j], sizeof this->signature);
        if (this->signature.sig[0] == this->b1 &&
            this->signature.sig[1] == this->b2 &&
            this->signature.sig[2] == this->b3)
        {
            // Signature found and known
            this->signatureKnown = true;
            return;
        }
    }
}


void SignaturePage::confirm()
{
	this->pageManager->changePage(new MainPage(this->pageManager));
}

void SignaturePage::initRender(SSD1306Ascii* display)
{
	display->println(F("Device Signature:"));
    
    // Display HEX signature
	display->print(F("HEX: "));
    DisplayUtils::printHex(display, this->b1);
    display->print(F(", "));
    DisplayUtils::printHex(display, this->b2);
    display->print(F(", "));
    DisplayUtils::printHex(display, this->b3);
    display->println();
    display->println();
    
    // Display device name
    display->print(F("-> "));
    if (this->signatureKnown)
        display->println(this->signature.desc);
    else
        display->println(F("Unknown signature"));
    
    // Display back button in bottom right
    const char* back = "> Back";
    display->setCursor(DISPLAY_COLUMNS - display->strWidth(back), DISPLAY_ROWS-1);
    display->print(back);
}
