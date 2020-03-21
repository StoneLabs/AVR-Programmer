#include "emptyPage.h"

EmptyPage::EmptyPage(PageManager* manager)
	: Page (manager)
{
}

void EmptyPage::render(SSD1306Ascii* display)
{
}
