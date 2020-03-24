#include "flashInitPage.h"

FlashInitPage::FlashInitPage(PageManager* manager, char* fileName)
	: LoadingPage ( manager, "Flashing file..." )
{
	this->fileName = fileName;
}

FlashInitPage::~FlashInitPage()
{
	delete this->fileName;
}

void FlashInitPage::init()
{
	Command command;
	command.cmd = cmd_flashFile;

	// Init command
	for (byte i = 0; i < COMMAND_DATASIZE; i++)
		command.data[i] = 0x00;

	// Copy filename to command data array
	memcpy(command.data, this->fileName, SFN_LENGTH);
	programmer_request(command);
}

void FlashInitPage::update()
{
	if (programmer_answer(answer))
	{
		if (answer.error > 0x00)
		{
			this->pageManager->changePage(new ErrorPage(this->pageManager, answer.error));
			return;
		}
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
