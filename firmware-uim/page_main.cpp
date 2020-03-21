#include "page_main.h"

MainPage::MainPage()
{
}

void MainPage::left()
{
    this->tabIndex--;
    this->tabIndex %= this->tabLength;
}

void MainPage::right()
{
    this->tabIndex++;
    this->tabIndex %= this->tabLength;
}

void MainPage::confirm()
{
    //todo
}

void MainPage::write_entry_line(SSD1306Ascii *display, byte index, const char* text)
{
    if (this->tabIndex == index)
        display->print("> ");
    else
        display->print("  ");
        
    display->println(text);
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
