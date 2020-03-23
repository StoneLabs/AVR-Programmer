#include "page.h"

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
}

void Page::right()
{
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
