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

class WriteFuseSelectInit2Page : public LoadingPage
{
private:
	Answer answer;
	byte sig1, sig2, sig3;

public:
	WriteFuseSelectInit2Page(PageManager* manager, byte sig1, byte sig2, byte sig3);
	
	void init() override;
	void update() override;
};