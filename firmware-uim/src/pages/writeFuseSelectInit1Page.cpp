#include "writeFuseSelectInit1Page.h"

WriteFuseSelectInit1Page::WriteFuseSelectInit1Page(PageManager* manager)
	: LoadingPage(manager, "Loading signature...")
{
}

void WriteFuseSelectInit1Page::init()
{
	programmer_request(cmd_readSignature);
}

void WriteFuseSelectInit1Page::update()
{
	if (programmer_answer(answer))
	{
		if (answer.error > 0x00)
		{
			this->pageManager->changePage(new ErrorPage(this->pageManager, answer.error));
			return;
		}
		if (answer.cmd == cmd_readSignature)
		{
			this->pageManager->changePage(
				new WriteFuseSelectInit2Page(this->pageManager,
					answer.data[0], answer.data[1], answer.data[2]));
			return;
		}
		else
		{
			Serial.println(F("CRITICAL: Invalid response to readSignature command."));
			while (true) {};
		}
	}
}