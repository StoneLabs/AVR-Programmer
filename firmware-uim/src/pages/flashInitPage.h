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
#include "flashPage.h"

class FlashInitPage : public LoadingPage
{
private:
	Answer answer;

public:
	FlashInitPage(PageManager* manager);

	void init() override;
	void update() override;
};