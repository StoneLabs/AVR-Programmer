#include "writeFusePage.h"

WriteFusePage::WriteFusePage(PageManager* manager)
	: Page ( manager )
{
}

void WriteFusePage::confirm()
{
	this->pageManager->changePage(new MainPage(this->pageManager));
}

void WriteFusePage::initRender(SSD1306Ascii* display)
{
	display->println(F("Fuse written."));

	// Display back button in bottom right
	const char* back = "> OK";
	display->setCursor(DISPLAY_COLUMNS - display->strWidth(back), DISPLAY_ROWS - 1);
	display->print(back);
}
