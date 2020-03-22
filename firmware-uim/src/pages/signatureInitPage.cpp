#include "signatureInitPage.h"

SignatureInitPage::SignatureInitPage(PageManager* manager)
	: LoadingPage(manager, "Loading...")
{
}

void SignatureInitPage::init()
{
	programmer_request(cmd_readSignature);
}

void SignatureInitPage::update()
{
	if (programmer_answer(answer))
	{
		if (answer.cmd == cmd_readSignature)
			this->pageManager->changePage(
				new SignaturePage(this->pageManager, 
					answer.data[0], answer.data[1], answer.data[2]));
		else
		{
			Serial.println(F("CRITICAL: Invalid response to readSignature command."));
			while (true) {};
		}
	}
}