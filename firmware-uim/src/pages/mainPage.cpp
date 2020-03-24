#include "mainPage.h"

MainPage::MainPage(PageManager* manager)
    : TabPage ( manager, 4 )
{
}

void MainPage::confirm()
{
    switch (this->getTabIndex())
    {
    case 0:
        this->pageManager->changePage(new SignatureInitPage(this->pageManager));
        break;
    case 1:
        this->pageManager->changePage(new EraseInitPage(this->pageManager));
        break;
    case 2:
        this->pageManager->changePage(new FlashSelectInitPage(this->pageManager));
        break;
    case 3:
        this->pageManager->changePage(new ReadFusesInitPage(this->pageManager));
        break;
    default:
        break;
    }
}

void MainPage::initRender(SSD1306Ascii* display)
{
    display->println(F("STONE LABS (TM) ISP."));
    display->println(F("  Read signature."));
    display->println(F("  Erase chip."));
    display->println(F("  Write HEX file."));
    display->println(F("  Read fuses."));
}

void MainPage::render(SSD1306Ascii *display)
{
    for (int i = 0; i < 4; i++)
    {
        display->setCursor(0, i + 1);
        if (this->getTabIndex() == i)
            display->print(F(">"));
        else
            display->print(F(" "));
    }
}
