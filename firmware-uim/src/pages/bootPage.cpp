#include "bootPage.h"

BootPage::BootPage(PageManager* manager, unsigned long minSplashTime)
	: LoadingPage ( manager, "STONE LABS.\n\nWelcome!", DISPLAY_COLUMNS - DISPLAY_COLUMNS_FONT, DISPLAY_ROWS - 1 )
{
    this->startTime = millis();
    this->minDelay = minSplashTime;
}

void BootPage::init()
{
    // Wait for the programmer to become ready
    pinMode(2, INPUT_PULLUP);
}

void BootPage::update()
{
    if (digitalRead(2) == LOW && millis() - startTime > this->minDelay)
    {
        // Send ping request only once when programmer comes online
        if (!this->programmerOn)
            programmer_request(cmd_ping);
        else
        {
            // Command allready send last iteration of update()
            if (programmer_answer(answer))
            {
                if (this->answer.cmd == cmd_ping && this->answer.data[0] == cmd_ping)
                {
                    this->pageManager->changePage(new MainPage(this->pageManager));
                    return;
                }
                else
                {
                    Serial.println(F("Illegal response to ping cmd."));
                    while (true) {};
                }
            }

        }
        // Dont send request again
        this->programmerOn = true;
    }
}
