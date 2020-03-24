#include "criticalErrorPage.h"

CriticalErrorPage::CriticalErrorPage(PageManager* manager, byte error)
	: Page ( manager )
{
	this->errorByte = error;
}

void CriticalErrorPage::initRender(SSD1306Ascii* display)
{
	display->println("A critical error occured!");
	display->println();
	display->print("Code: ");
	DisplayUtils::printHex(display, this->errorByte);

	display->setCursor(0, DISPLAY_ROWS - 1);
	display->print("Manual restart required!");
}
