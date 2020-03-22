#include "pageManager.h"

PageManager::PageManager(SSD1306Ascii* display)
{
	this->display = display;
	this->currentPage = new EmptyPage(this);
}

PageManager::~PageManager()
{
	delete this->currentPage;
}

void PageManager::left() 
{
	this->currentPage->left();
	this->render();
}

void PageManager::right() 
{
	this->currentPage->right();
	this->render();
}

void PageManager::confirm() 
{
	this->currentPage->confirm();
	this->render();
}

void PageManager::updatePage()
{
	// Update page
	this->currentPage->update();

	// Check if rendering is necessary
	if (this->currentPage->needsRender())
		this->render();
}

void PageManager::render()
{
	this->currentPage->render(this->display);
}

void PageManager::changePage(Page* page)
{
	delete this->currentPage;
	this->currentPage = page;

	// Init page
	this->currentPage->init();

	// Render the target once
	this->display->clear();
	this->currentPage->initRender(this->display);
	this->render();
}
