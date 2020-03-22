#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <SSD1306Ascii.h>
#include "../pageManager.h"
#include "loadingPage.h"
#include "mainPage.h"

class DelayPage : public LoadingPage
{
private:
	unsigned long delayMillis = 0UL;

public:
	DelayPage(PageManager* manager, Page* targetPage, unsigned long timeout);

	bool changePage() override;
};