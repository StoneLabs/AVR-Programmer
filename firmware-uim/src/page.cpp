#include "page.h"


Page::Page(PageManager* manager)
{
    this->pageManager = manager;
}

Page::~Page()
{
}

void Page::left()
{
    this->tabIndex--;
    this->tabIndex %= this->tabLength;
}

void Page::right()
{
    this->tabIndex++;
    this->tabIndex %= this->tabLength;
}

void Page::update()
{
}

void Page::confirm()
{
}

bool Page::needsRender()
{
    return false;
}

void Page::initRender(SSD1306Ascii* display)
{
}

void Page::write_entry_line(SSD1306Ascii* display, byte index, const char* text)
{
    if (this->tabIndex == index)
        display->print("> ");
    else
        display->print("  ");

    display->println(text);
}