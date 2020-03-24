#include "readFusesInitPage.h"

ReadFusesInitPage::ReadFusesInitPage(PageManager* manager)
	: LoadingPage(manager, "Reading fuses...")
{
}

void ReadFusesInitPage::init()
{
	programmer_request(cmd_readFuses);
}

void ReadFusesInitPage::update()
{
	if (programmer_answer(answer))
	{
		if (answer.error > 0x00)
		{
			this->pageManager->changePage(new ErrorPage(this->pageManager, answer.error));
			return;
		}
		if (answer.cmd == cmd_readFuses)
		{
			this->pageManager->changePage(
				new ReadFusesPage(this->pageManager,
					answer.data[lowFuse], answer.data[highFuse], answer.data[extFuse],
					answer.data[lockFuse], answer.data[calibrationFuse]));
			return;
		}
		else
		{
			Serial.println(F("CRITICAL: Invalid response to readSignature command."));
			while (true) {};
		}
	}
}