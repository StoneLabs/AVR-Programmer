#include "writeFuseSelectInitPage.h"

WriteFuseSelectInitPage::WriteFuseSelectInitPage(PageManager* manager)
	: LoadingPage ( manager, "Loading..." )
{
}

void WriteFuseSelectInitPage::init()
{
	programmer_request(cmd_readFuses);
}

void WriteFuseSelectInitPage::update()
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
				new WriteFuseSelectPage(this->pageManager,
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
