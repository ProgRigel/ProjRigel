#include "app.h"
#include <rggui\rg_gui_context.h>

RigelApp::RigelApp()
{
	RgWindowSettings settings;
	RgWindowManager::createWindow(&m_pWindow, &settings);

	m_pWindow->EventOnRegister.connect<RigelApp, &RigelApp::onRegisterWindow>(this);
	m_pWindow->EventOnFrame.connect<RigelApp, &RigelApp::onRender>(this);
	auto& windowmgr = RgWindowManager::getInstance();
	windowmgr.registerWindow(m_pWindow);
	m_pWindow->showWindow();
}

RigelApp::~RigelApp()
{
	m_pAppGraphics->Release();
	delete m_pAppGraphics;

	RgWindowManager::getInstance().releaseWindow();
}



void RigelApp::onRegisterWindow()
{
	m_pAppGraphics = new RigelAppGraphics();
	m_pAppGraphics->Init(m_pWindow);

	RgGUIContext *guictx = nullptr;
	RgGUI::CreateRgGUIContext(&guictx);
	guictx->Release();

	RgGUI::Release();
	
}

void RigelApp::Run()
{
	RgWindowManager::getInstance().enterMainLoop();
}

void RigelApp::onRender()
{
	m_pAppGraphics->Render();
}
