#include "initPage.h"

InitPage::InitPage(PageManager* manager, Page* targetPage)
	: LoadingPage(manager, targetPage)
{
}

void InitPage::init()
{
	programmer_request(cmd_ping);
}

bool InitPage::changePage()
{
	if (programmer_answer(answer))
	{
		if (answer.cmd == cmd_ping && answer.data[0] == cmd_ping)
			return true;
		else
		{
			Serial.println(F("CRITICAL: Invalid response to ping command."));
			while (true) {};
		}
	}
	return false;
}
