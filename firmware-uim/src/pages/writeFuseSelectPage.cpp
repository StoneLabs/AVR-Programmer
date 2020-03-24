#include "writeFuseSelectPage.h"

WriteFuseSelectPage::WriteFuseSelectPage(PageManager* manager)
    : TabPage(manager, 5)
{
}

void WriteFuseSelectPage::confirm()
{
    if (this->getTabIndex() == 4) // Back
    {
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
