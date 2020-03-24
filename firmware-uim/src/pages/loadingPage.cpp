#include "loadingPage.h"

LoadingPage::LoadingPage(PageManager* manager, const char* message)
	: Page(manager)
{
	this->initMillis = millis();
	this->message = message;
}
LoadingPage::LoadingPage(PageManager* manager, const char* message, byte manualColumn, byte manualRow)
	: LoadingPage(manager, message)
{
	this->symbolOffset = manualColumn;
	this->manualRow = manualRow;
	this->manualPos = true;
}

unsigned long LoadingPage::getInitMillis()
{
	return this->initMillis;
}

bool LoadingPage::needsRender()
{
	// Cycle symbol from 0-4 every 200ms
	byte nsymbol = (millis() - this->initMillis) / 200 % 4;
	if (nsymbol != this->symbol)
	{
		this->symbol = nsymbol;
		return true;
	}
	return false;
}

void LoadingPage::initRender(SSD1306Ascii* display)
{
	display->print(this->message);
	if (!this->manualPos)
		this->symbolOffset = display->strWidth(this->message);
}

void LoadingPage::render(SSD1306Ascii* display)
{
	// Require monospace
	display->setCursor(this->symbolOffset, this->manualRow);

	switch (this->symbol)
	{
	case 0: display->print(F("|")); break;
	case 1: display->print(F("/")); break;
	case 2: display->print(F("-")); break;
	case 3: display->print(F("\\")); break;
	}
}
