#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <SSD1306Ascii.h>
#include "../page.h"
#include "../pageManager.h"
#include "signatureInitPage.h"
#include "eraseInitPage.h"
#include "readFusesInitPage.h"

class MainPage : public Page
{
public:
	MainPage(PageManager* manager);
	void confirm() override;

	void initRender(SSD1306Ascii* display) override;
	void render(SSD1306Ascii *display) override;
};