#include "writeFuseInitPage.h"

WriteFuseInitPage::WriteFuseInitPage(PageManager* manager, byte fuse, byte value)
	: LoadingPage(manager, "Setting fuse...")
{
	this->fuse = fuse;
	this->value = value;
}

void WriteFuseInitPage::init()
{
	Command command;
	
	switch (this->fuse)
	{
	case lowFuse:
		command.cmd = cmd_writeLowFuse;
		break;
	case highFuse:
		command.cmd = cmd_writeHighFuse;
		break;
	case extFuse:
		command.cmd = cmd_writeExtFuse;
		break;
	case lockFuse:
		command.cmd = cmd_writeLockFuse;
		break;
	default:
		Serial.println(F("Unknown fuse byte."));
		while (true) {};
	}
	this->command = command.cmd; // For later comparison

	// Init command
	for (byte i = 0; i < COMMAND_DATASIZE; i++)
		command.data[i] = 0x00;

	// Write first two bytes with fuse value
	command.data[0] = this->value;
	command.data[1] = this->value;

	// Send request
	programmer_request(command);
}

void WriteFuseInitPage::update()
{
	if (programmer_answer(answer))
	{
		if (answer.error > 0x00)
		{
			this->pageManager->changePage(new ErrorPage(this->pageManager, answer.error));
			return;
		}
		if (answer.cmd == this->command)
		{
			this->pageManager->changePage(new WriteFusePage(this->pageManager));
			return;
		}
		else
		{
			Serial.println(F("CRITICAL: Invalid response to flash command."));
			while (true) {};
		}
	}
}
