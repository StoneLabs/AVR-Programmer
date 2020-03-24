#include "criticalErrorPage.h"

CriticalErrorPage::CriticalErrorPage(PageManager* manager, byte error)
	: Page ( manager )
{
	this->errorByte = error;
}

void CriticalErrorPage::initRender(SSD1306Ascii* display)
{
	display->println(F("CRITICAL ERROR"));
	display->println();
	display->print(F("Code: "));
	DisplayUtils::printHex(display, this->errorByte);

	display->setCursor(0, DISPLAY_ROWS - 1);
	display->print(F("Manual restart req.!"));
}
