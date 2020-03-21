#include "mainPage.h"

MainPage::MainPage(PageManager* manager)
    : Page (manager)
{
}

void MainPage::confirm()
{
    //todo
}

void MainPage::render(SSD1306Ascii *display)
{
	display->clear();
    display->println("STONE LABS (TM) ISP.");
    this->write_entry_line(display, 0, "Read signature.");
    this->write_entry_line(display, 1, "Erase chip.");
    this->write_entry_line(display, 2, "Write HEX file.");
    this->write_entry_line(display, 3, "Set fuses.");
}
