#include "delayPage.h"

DelayPage::DelayPage(PageManager* manager, unsigned long time, Page* targetPage)
	: Page (manager)
{
	this->initMillis = millis();
	this->delayMillis = time;
	this->targetPage = targetPage;
}

void DelayPage::update()
{
	if (millis() - this->initMillis > this->delayMillis)
	{
		this->pageManager->changePage(this->targetPage);
	}
}

bool DelayPage::needsRender()
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

void DelayPage::initRender(SSD1306Ascii* display)
{
	display->print(this->message);
	this->symbolOffset = display->strWidth(this->message);
}

void DelayPage::render(SSD1306Ascii* display)
{
	// Require monospace
	display->setCursor(this->symbolOffset, 0);

	switch (this->symbol)
	{
	case 0: display->println("|"); break;
	case 1: display->println("/"); break;
	case 2: display->println("-"); break;
	case 3: display->println("\\"); break;
	}
}
