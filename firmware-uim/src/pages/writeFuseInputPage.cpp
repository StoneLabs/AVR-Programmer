#include "writeFuseInputPage.h"

WriteFuseInputPage::WriteFuseInputPage(PageManager* manager, byte fuse, byte initValue)
	: TabPage ( manager, 10 )
{
    this->fuse = fuse;
    this->fuseValue = initValue;
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
        return;
    }
}

void WriteFuseInputPage::initRender(SSD1306Ascii* display)
{
    display->println(F("Change fuse bits."));

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
