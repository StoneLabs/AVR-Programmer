#include "writeFuseSelectPage.h"

WriteFuseSelectPage::WriteFuseSelectPage(PageManager* manager, byte sig1, byte sig2, byte sig3, byte lowFuse, byte highFuse, byte extFuse, byte lockFuse, byte calibration)
    : TabPage(manager, 5)
{
    this->sig1 = sig1;
    this->sig2 = sig2;
    this->sig3 = sig3;

    this->val_lowFuse = lowFuse;
    this->val_highFuse = highFuse;
    this->val_extFuse = extFuse;
    this->val_lockFuse = lockFuse;
    this->val_calibration = calibration;
}

void WriteFuseSelectPage::confirm()
{
    switch (this->getTabIndex())
    {
    case 0: // Low
        this->pageManager->changePage(new WriteFuseInputPage(
            this->pageManager, this->sig1, this->sig2, this->sig3, lowFuse, this->val_lowFuse));
        return;
    case 1: // High
        this->pageManager->changePage(new WriteFuseInputPage(
            this->pageManager, this->sig1, this->sig2, this->sig3, highFuse, this->val_highFuse));
        return;
    case 2: // Ext
        this->pageManager->changePage(new WriteFuseInputPage(
            this->pageManager, this->sig1, this->sig2, this->sig3, extFuse, this->val_extFuse));
        return;
    case 3: // Lock
        this->pageManager->changePage(new WriteFuseInputPage(
            this->pageManager, this->sig1, this->sig2, this->sig3, lockFuse, this->val_lockFuse));
        return;
    case 4:
        this->pageManager->changePage(new MainPage(this->pageManager));
        return;
    }
}

void WriteFuseSelectPage::initRender(SSD1306Ascii* display)
{
    display->println(F("Select fuse to write"));
    display->println(F("  Low fuse"));
    display->println(F("  High fuse"));
    display->println(F("  Ext. fuse"));
    display->println(F("  Lock bits"));

    display->setCursor(DISPLAY_COLUMNS - display->strWidth(back), DISPLAY_ROWS - 1);
    display->print(this->back);
}

void WriteFuseSelectPage::render(SSD1306Ascii* display)
{
    for (int i = 0; i < 4; i++)
    {
        display->setCursor(0, i + 1);
        if (this->getTabIndex() == i)
            display->print(F(">"));
        else
            display->print(F(" "));
    }

    display->setCursor(DISPLAY_COLUMNS - display->strWidth(back), DISPLAY_ROWS - 1);
    if (this->getTabIndex() == 4)
        display->print(F(">"));
    else
        display->print(F(" "));
}
