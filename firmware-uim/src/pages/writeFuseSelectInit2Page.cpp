#include "writeFuseSelectInit2Page.h"

WriteFuseSelectInit2Page::WriteFuseSelectInit2Page(PageManager* manager, byte sig1, byte sig2, byte sig3)
	: LoadingPage ( manager, "Loading fuses..." )
{
	this->sig1 = sig1;
	this->sig2 = sig2;
	this->sig3 = sig3;
}

void WriteFuseSelectInit2Page::init()
{
	programmer_request(cmd_readFuses);
}

void WriteFuseSelectInit2Page::update()
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
				new WriteFuseSelectPage(this->pageManager, this->sig1, this->sig2, this->sig3,
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
