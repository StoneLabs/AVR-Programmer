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

class WriteFusePage : public Page
{
public:
	WriteFusePage(PageManager* manager);

	void confirm() override;
	void initRender(SSD1306Ascii* display) override;
};