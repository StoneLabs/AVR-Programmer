#include "mainInitPage.h"

MainInitPage::MainInitPage(PageManager* manager)
	: LoadingPage(manager, (char*)"Loading...")
{
}

void MainInitPage::init()
{
	programmer_request(cmd_ping);
}

void MainInitPage::update()
{
	if (programmer_answer(answer))
	{
		if (answer.cmd == cmd_ping && answer.data[0] == cmd_ping)
			this->pageManager->changePage(new MainPage(this->pageManager));
		else
		{
			Serial.println(F("CRITICAL: Invalid response to ping command."));
			while (true) {};
		}
	}
}
