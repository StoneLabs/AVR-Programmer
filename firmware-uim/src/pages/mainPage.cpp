#include "mainPage.h"

MainPage::MainPage(PageManager* manager)
    : Page (manager)
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
    case 3:
        this->pageManager->changePage(new ReadFusesInitPage(this->pageManager));
        break;
    default:
        break;
    }
}

void MainPage::initRender(SSD1306Ascii* display)
{
    display->println("STONE LABS (TM) ISP.");
    display->println("  Read signature.");
    display->println("  Erase chip.");
    display->println("  Write HEX file.");
    display->println("  Read fuses.");
}

void MainPage::render(SSD1306Ascii *display)
{
    for (int i = 0; i < 4; i++)
    {
        display->setCursor(0, i + 1);
        if (this->getTabIndex() == i)
            display->print('>');
        else
            display->print(' ');
    }
}
