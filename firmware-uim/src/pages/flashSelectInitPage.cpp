#include "flashSelectInitPage.h"

FlashSelectInitPage::FlashSelectInitPage(PageManager* manager)
	: LoadingPage(manager, "Reading...")
{
}

void FlashSelectInitPage::init()
{
	programmer_request(cmd_openNextFile);
}

void FlashSelectInitPage::update()
{
	if (programmer_answer(answer))
	{
		if (answer.cmd == cmd_openNextFile)
		{
			char* fileName = new char[SFN_LENGTH];
			memcpy(fileName, answer.data, SFN_LENGTH);
			fileName[SFN_LENGTH - 1] = 0x00; // Terminate string JIC

			this->pageManager->changePage(
				new FlashSelectPage(this->pageManager, fileName));
		}
		else
		{
			Serial.println(F("CRITICAL: Invalid response to readSignature command."));
			while (true) {};
		}
	}
}