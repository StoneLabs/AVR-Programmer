#include "writeFuseInputPage.h"

WriteFuseInputPage::WriteFuseInputPage(PageManager* manager, byte sig1, byte sig2, byte sig3, byte fuse, byte initValue)
	: TabPage ( manager, 10 )
{
    this->sig1 = sig1;
    this->sig2 = sig2;
    this->sig3 = sig3;

    this->fuse = fuse;
    this->fuseValue = initValue;
}

void WriteFuseInputPage::init()
{
    for (byte j = 0; j < NUMITEMS(signatures); j++)
    {
        // Copy from PROGMEM to Memory
        memcpy_P(&this->signature, &signatures[j], sizeof this->signature);
        if (this->signature.sig[0] == this->sig1 &&
            this->signature.sig[1] == this->sig2 &&
            this->signature.sig[2] == this->sig3)
        {
            // Signature found and known
            this->signatureKnown = true;
            return;
        }
    }
}

void WriteFuseInputPage::confirm()
{
    if (this->getTabIndex() < 8)
    {
        this->fuseValue ^= bit(7 - this->getTabIndex());
    }
    else if (this->getTabIndex() == 8)
    {
        // Cancel
        this->pageManager->changePage(new MainPage(this->pageManager));
        return;
    }
    else if (this->getTabIndex() == 9)
    {
        //OK
        this->pageManager->changePage(new WriteFuseInitPage(this->pageManager, this->fuse, this->fuseValue));
        return;
    }
}

void WriteFuseInputPage::initRender(SSD1306Ascii* display)
{
    display->println(F("Change fuse bits."));

    // Print chip name or signature if unknown
    display->setCursor(0, 1);
    if (this->signatureKnown)
        display->println(this->signature.desc);
    else
    {
        display->print(F("Signature: "));
        DisplayUtils::printHex(display, this->sig1);
        display->print(F(","));
        DisplayUtils::printHex(display, this->sig2);
        display->print(F(","));
        DisplayUtils::printHex(display, this->sig3);
    }

    display->setCursor(0, 3);
    switch (this->fuse)
    {
    case lowFuse:
        display->println(F("Low:"));
        break;
    case highFuse:
        display->println(F("High:"));
        break;
    case extFuse:
        display->println(F("Ext.:"));
        break;
    case lockFuse:
        display->println(F("Lock:"));
        break;
    }

    // Display Fuse bit name prefix
    if (this->fuse == lowFuse ||
        this->fuse == extFuse ||
        this->fuse == highFuse)
    {
        display->setCursor(0, 5);
        display->print(F("->"));
    }

    display->setCursor(0, DISPLAY_ROWS - 1);
    display->print(this->back);
    display->setCursor(DISPLAY_COLUMNS - display->strWidth(this->ok), DISPLAY_ROWS - 1);
    display->print(this->ok);
}

void WriteFuseInputPage::render(SSD1306Ascii* display)
{
    display->setCursor(6 * DISPLAY_COLUMNS_FONT, 3);
    display->print("0b");
    DisplayUtils::printBin(display, this->fuseValue);

    // Plus 2 because the ^ character is offcenter
    display->setCursor(8 * DISPLAY_COLUMNS_FONT + 2, 4);
    for (byte bit = 0; bit < 8; bit++)
    {
        if (bit == this->getTabIndex())
            display->print("^");
        else
            display->print(" ");
    }

    // Display Fuse bit name if chip signature is known
    display->setCursor(3 * DISPLAY_COLUMNS_FONT, 5);
    if (this->signatureKnown)
    {
        if (this->getTabIndex() < 8)
        {
            // Allocate buffer for name of bit and copy from PROGMEM
            char bitName[FBIT_MAX_LENGTH] = "";
            switch (this->fuse)
            {
            case lowFuse:
                strcpy_P(bitName, this->signature.lowFuseNames[this->getTabIndex()]);
                break;
            case highFuse:
                strcpy_P(bitName, this->signature.highFuseNames[this->getTabIndex()]);
                break;
            case extFuse:
                strcpy_P(bitName, this->signature.extFuseNames[this->getTabIndex()]);
                break;
            }
            display->clearToEOL();
            display->println(bitName);
        }
        else
            // Back or Confirm button
            display->clearToEOL();
    }

    display->setCursor(0, DISPLAY_ROWS - 1);
    if (this->getTabIndex() == 8)
        display->print(F(">"));
    else
        display->print(F(" "));

    display->setCursor(DISPLAY_COLUMNS - display->strWidth(this->ok), DISPLAY_ROWS - 1);
    if (this->getTabIndex() == 9)
        display->print(F(">"));
    else
        display->print(F(" "));
}
