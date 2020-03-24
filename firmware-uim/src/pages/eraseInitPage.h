#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "../../I2CHelper.h"
#include "../pageManager.h"
#include "loadingPage.h"
#include "erasePage.h"
#include "errorPage.h"

class EraseInitPage : public LoadingPage
{
private:
	Answer answer;

public:
	EraseInitPage(PageManager* manager);

	void init() override;
	void update() override;
};