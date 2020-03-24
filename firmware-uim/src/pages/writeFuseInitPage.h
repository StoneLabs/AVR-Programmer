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
#include "writeFusePage.h"
#include "errorPage.h"

class WriteFuseInitPage : public LoadingPage
{
private:
	Answer answer;
	byte fuse, value;
	byte command;

public:
	WriteFuseInitPage(PageManager* manager, byte fuse, byte value);

	void init() override;
	void update() override;
};