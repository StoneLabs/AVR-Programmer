#include "eraseInitPage.h"

EraseInitPage::EraseInitPage(PageManager* manager)
	: LoadingPage(manager, "Erasing chip...")
{
}

void EraseInitPage::init()
{
	programmer_request(cmd_erase);
}

void EraseInitPage::update()
{
	if (programmer_answer(answer))
	{
		if (answer.cmd == cmd_erase)
		{
			this->pageManager->changePage(
				new ErasePage(this->pageManager));
			return;
		}
		else
		{
			Serial.println(F("CRITICAL: Invalid response to erase command."));
			while (true) {};
		}
	}
}
