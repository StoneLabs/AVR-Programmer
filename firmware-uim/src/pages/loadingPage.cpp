#include "loadingPage.h"

LoadingPage::LoadingPage(PageManager* manager, Page* targetPage)
	: Page(manager)
{
	this->initMillis = millis();
	this->targetPage = targetPage;
}

unsigned long LoadingPage::getInitMillis()
{
	return this->initMillis;
}

void LoadingPage::update()
{
	if (this->changePage())
		this->pageManager->changePage(this->targetPage);
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
	this->symbolOffset = display->strWidth(this->message);
}

void LoadingPage::render(SSD1306Ascii* display)
{
	// Require monospace
	display->setCursor(this->symbolOffset, 0);

	switch (this->symbol)
	{
	case 0: display->print("|"); break;
	case 1: display->print("/"); break;
	case 2: display->print("-"); break;
	case 3: display->print("\\"); break;
	}
}
