#include "page.h"

byte Page::getTabIndex() const
{
    return this->tabIndex;
}

Page::Page(PageManager* manager)
{
    this->pageManager = manager;
}

Page::~Page()
{
}

void Page::init()
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

void Page::render(SSD1306Ascii* display)
{
}
