#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <SSD1306Ascii.h>
#include "../page.h"
#include "../pageManager.h"
#include "../signatures.h"
#include "../displayUtils.h"
#include "writeFuseSelectPage.h"
#include "mainPage.h"

class WriteFuseSelectInitPage : public LoadingPage
{
private:
	Answer answer;

public:
	WriteFuseSelectInitPage(PageManager* manager);
	
	void init() override;
	void update() override;
};