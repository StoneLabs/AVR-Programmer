#include "delayPage.h"

DelayPage::DelayPage(PageManager* manager, Page* targetPage, unsigned long time, char* message)
	: LoadingPage (manager, message)
{
	this->targetPage = targetPage;
	this->delayMillis = time;
}

void DelayPage::update()
{
	if (millis() - this->getInitMillis() > this->delayMillis)
		this->pageManager->changePage(this->targetPage);
}
