#include "stdafx.h"
#include "app.h"
#include "app_graphics.h"
#include <rggui\rg_gui_context.h>
#include <rggraphics\rg_render_context.h>
#include "editor_gui.h"

namespace editor {

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
		m_pEditorGUI->Release();
		delete m_pEditorGUI;
		m_pEditorGUI = nullptr;

		m_pAppGraphics->Release();
		delete m_pAppGraphics;
		m_pAppGraphics = nullptr;

		RgWindowManager::getInstance().releaseWindow();
	}


	void RigelApp::onRegisterWindow()
	{
		m_pAppGraphics = new RigelAppGraphics();
		m_pAppGraphics->Init(m_pWindow);

		m_pEditorGUI = new EditorGUI();
		m_pEditorGUI->BindGraphics(m_pAppGraphics->m_pRgGraphicsCtx);

		m_pWindow->EventOnGUI.connect<EditorGUI, &EditorGUI::OnWindowGUI>(m_pEditorGUI);
	}

	void RigelApp::Run()
	{
		RgWindowManager::getInstance().enterMainLoop();
	}

	void RigelApp::onRender()
	{

		auto ctx = m_pAppGraphics->m_pRgGraphicsCtx;
		m_pEditorGUI->OnRender();

		ctx->render();
	}

}
