#include "flashInitPage.h"

FlashInitPage::FlashInitPage(PageManager* manager)
	: LoadingPage ( manager, "Flashing file..." )
{
}

void FlashInitPage::init()
{
	programmer_request(cmd_flashFile);
}

void FlashInitPage::update()
{
	if (programmer_answer(answer))
	{
		if (answer.cmd == cmd_flashFile)
		{
			this->pageManager->changePage(new FlashPage(this->pageManager));
			return;
		}
		else
		{
			Serial.println(F("CRITICAL: Invalid response to flash command."));
			while (true) {};
		}
	}
}
