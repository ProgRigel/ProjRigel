#include "stdafx.h"
#include "editor_gui.h"
#include <rggui\rg_gui.h>
#include <rggui\rg_gui_bind_graphics.h>

using namespace rg;

namespace editor {
	EditorGUI::EditorGUI()
	{
		RgGUI::CreateRgGUIContext(&m_pGUIContext);
	}
	EditorGUI::~EditorGUI()
	{
		Release();
	}
	void EditorGUI::Release()
	{
		if (m_pBindGraphics != nullptr) {
			m_pBindGraphics->Release();
		}
		m_pBindGraphics = nullptr;

		RgGUI::Release(&m_pGUIContext);
		m_pGUIContext = nullptr;
	}
	void EditorGUI::BindGraphics(rg::RgGraphicsContext * graphicsCtx)
	{
		if (m_pBindGraphics != nullptr) {
			m_pBindGraphics->Release();
		}
		m_pBindGraphics = new RgGUIBindGraphics(m_pGUIContext, graphicsCtx);
	}
	void EditorGUI::OnWindowGUI(const rg::RgWindowEvent e)
	{

		auto ctx = m_pGUIContext;

		static bool initResize = false;
		if (e.Type == RgWindowEventType::Resize && initResize) {
			initResize = true;
			return;
		}

		//if (e.Type == RgWindowEventType::Resize) return;

		ctx->BeginGUI(e);

		ctx->BeginGroup(RgVec2(10, 30), RgVec2(400, 300));


		//menu
		ctx->GUIMenuBarBegin(true);

		ctx->SetColor(RgGUIColors::Wetasphalt);
		if (ctx->GUIMenuItem()) {
			RgLogD() << "menuitem 1";
		}
		ctx->SetColor(RgGUIColors::Asbestos);
		if (ctx->GUIMenuItem()) {
			RgLogD() << "menuitem 2";
		}
		ctx->SetColor(RgGUIColors::SunFlower);
		if (ctx->GUIMenuItem()) {
			RgLogD() << "menuitem 3";
		}

		if (ctx->GUIButton(RgVec2(30, 20), RgVec2(50, 50))){
			RgLogD() << "button 1";
		}

		ctx->GUIMenuBarEnd();


		ctx->EndGroup();


		ctx->EndGUI();


	}
	void EditorGUI::OnRender()
	{
		m_pBindGraphics->OnRender();
	}
}


