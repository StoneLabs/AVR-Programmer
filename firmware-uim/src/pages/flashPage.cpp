#include "flashPage.h"

FlashPage::FlashPage(PageManager* manager)
	: Page ( manager )
{
}

void FlashPage::confirm()
{
	this->pageManager->changePage(new MainInitPage(this->pageManager));
}

void FlashPage::initRender(SSD1306Ascii* display)
{
	display->println("Flash complete.");
	display->println();
	display->println("Please check fuses!");

	// Display back button in bottom right
	const char* back = "> OK";
	display->setCursor(DISPLAY_COLUMNS - display->strWidth(back), DISPLAY_ROWS - 1);
	display->print(back);
}
