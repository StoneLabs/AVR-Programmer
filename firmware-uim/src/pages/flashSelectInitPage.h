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
#include "flashSelectPage.h"

class FlashSelectInitPage : public LoadingPage
{
private:
	Answer answer;

public:
	FlashSelectInitPage(PageManager* manager);

	void init() override;
	void update() override;
};