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
#include "writeFuseSelectInit2Page.h"
#include "errorPage.h"

class WriteFuseSelectInit1Page : public LoadingPage
{
private:
	Answer answer;

public:
	WriteFuseSelectInit1Page(PageManager* manager);

	void init() override;
	void update() override;
};
