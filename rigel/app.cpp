#include "app.h"

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
	RgGraphicsAPI::ReleaseAPI(m_pGraphicsCtx);
	m_pGraphicsCtx = nullptr;
	RgWindowManager::getInstance().releaseWindow();
}

void RigelApp::Run()
{
	//create shader test
	RgShaderOptions options;

	std::wstring fpath = GetWorkDirectory();
	fpath.append(L"/vs.hlsl");
	m_pGraphicsCtx->CompileShaderFromFile(fpath, options);

	RgWindowManager::getInstance().enterMainLoop();
}

void RigelApp::onRegisterWindow()
{
	//init graphics
	RG_GRAPHICS_INIT_SETTINGS settings;
	settings.Windowed = true;
	settings.OutputWindow = (HWND)m_pWindow->getHandler();
	settings.BufferHeight = m_pWindow->getHeight();
	settings.BufferWidth = m_pWindow->getWidth();
	m_pGraphicsCtx = RgGraphicsAPI::InitAPI(RG_GRAPHICS_APY_DX11, &settings);
}

void RigelApp::onRender()
{
	if (m_pGraphicsCtx)
		m_pGraphicsCtx->render();
}
