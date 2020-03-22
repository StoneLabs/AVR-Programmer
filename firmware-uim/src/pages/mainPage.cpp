#include "mainPage.h"

MainPage::MainPage(PageManager* manager)
    : Page (manager)
{
}

void MainPage::confirm()
{
    //todo
}

void MainPage::initRender(SSD1306Ascii* display)
{
    display->println("STONE LABS (TM) ISP.");
    display->println("  Read signature.");
    display->println("  Erase chip.");
    display->println("  Write HEX file.");
    display->println("  Set fuses.");
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
