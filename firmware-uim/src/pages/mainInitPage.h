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

class MainInitPage : public LoadingPage
{
private:
	unsigned long delayMillis = 0UL;
	Answer answer;

public:
	MainInitPage(PageManager* manager);

	void init() override;
	void update() override;
};
