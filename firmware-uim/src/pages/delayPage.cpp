#include "delayPage.h"

DelayPage::DelayPage(PageManager* manager, Page* targetPage, unsigned long time)
	: LoadingPage (manager, targetPage)
{
	this->delayMillis = time;
}

bool DelayPage::changePage()
{
	return millis() - this->getInitMillis() > this->delayMillis;
}
