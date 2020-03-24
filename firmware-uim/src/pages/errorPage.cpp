#include "errorPage.h"

ErrorPage::ErrorPage(PageManager* manager, byte error)
	: Page ( manager )
{
	this->errorByte = error;
}

void ErrorPage::confirm()
{
	this->pageManager->changePage(new MainPage(this->pageManager));
}

void ErrorPage::initRender(SSD1306Ascii* display)
{
	display->print("Error: ");
	DisplayUtils::printHex(display, this->errorByte);
	
	display->setCursor(0, 3);
	switch (errorByte)
	{
	case error_ProgrammingMode:
		display->println("Coudn't enter pro-");
		display->println("gramming mode.");
		break;
	default:
		display->println("Unknown error.");
		break;
	}

	// Display back button in bottom right
	const char* back = "> OK";
	display->setCursor(DISPLAY_COLUMNS - display->strWidth(back), DISPLAY_ROWS - 1);
	display->print(back);
}
