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
		//if (e.Type == RgWindowEventType::Resize) return;

		ctx->BeginGUI(e);

		ctx->BeginGroup(RgVec2(10, 30), RgVec2(400, 300));

		ctx->GUIMenuBarBegin(true);

		ctx->GUIMenuBarEnd();

		ctx->EndGroup();

		ctx->EndGUI();


	}
	void EditorGUI::OnRender()
	{
		m_pBindGraphics->OnRender();
	}
}


