#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <SSD1306Ascii.h>
#include "../../I2CHelper.h"
#include "../pageManager.h"
#include "loadingPage.h"
#include "mainPage.h"
#include "criticalErrorPage.h"

class BootPage : public LoadingPage
{
private:
	bool programmerOn = false;
	unsigned long startTime = 0;
	unsigned long minDelay = 0;
	Answer answer;

public:
	BootPage(PageManager* manager, unsigned long minSplashTime = 0);

	void init() override;
	void update() override;
};
