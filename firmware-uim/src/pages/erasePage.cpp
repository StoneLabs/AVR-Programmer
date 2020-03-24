#include "erasePage.h"

ErasePage::ErasePage(PageManager* manager)
	: Page (manager)
{
}

void ErasePage::confirm()
{
	this->pageManager->changePage(new MainPage(this->pageManager));
}

void ErasePage::initRender(SSD1306Ascii* display)
{
	display->println(F("Chip erased."));

	// Display back button in bottom right
	const char* back = "> Back";
	display->setCursor(DISPLAY_COLUMNS - display->strWidth(back), DISPLAY_ROWS - 1);
	display->print(back);
}
