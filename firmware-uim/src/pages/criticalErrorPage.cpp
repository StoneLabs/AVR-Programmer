#include "criticalErrorPage.h"

CriticalErrorPage::CriticalErrorPage(PageManager* manager, byte error)
	: Page ( manager )
{
	this->errorByte = error;
}

void CriticalErrorPage::initRender(SSD1306Ascii* display)
{
	display->println("CRITICAL ERROR");
	display->println();
	display->print("Code: ");
	DisplayUtils::printHex(display, this->errorByte);

	display->setCursor(0, DISPLAY_ROWS - 1);
	display->print("Manual restart req.!");
}
