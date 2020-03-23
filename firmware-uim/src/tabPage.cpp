#include "tabPage.h"

byte TabPage::getTabIndex() const
{
    return this->tabIndex;
}

TabPage::TabPage(PageManager* manager, byte tabLength)
    : Page ( manager ), tabLength (tabLength)
{
}

void TabPage::left()
{
    this->tabIndex--;
    this->tabIndex %= this->tabLength;
}

void TabPage::right()
{
    this->tabIndex++;
    this->tabIndex %= this->tabLength;
}