#include "bootPage.h"

BootPage::BootPage(PageManager* manager)
	: LoadingPage ( manager, "Booting..." )
{
}

void BootPage::init()
{
    // Wait for the programmer to become ready
    pinMode(2, INPUT_PULLUP);
}

void BootPage::update()
{
    if (digitalRead(2) == LOW)
        this->pageManager->changePage(new MainInitPage(this->pageManager));
}
