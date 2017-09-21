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

		//if (e.Type == RgWindowEventType::Resize) return;

		m_pGUIContext->BeginGUI(e);

		m_pGUIContext->SetColor(RgGUIColors::Pumpkin);
		m_pGUIContext->DrawRect(RgVec2(10, 30), RgVec2(50, 50));
		
		m_pGUIContext->BeginGroup(RgVec2(10, 30), RgVec2(50, 50));

		m_pGUIContext->SetColor(RgGUIColors::Clouds);
		m_pGUIContext->DrawRect(RgVec2(-10,0), RgVec2(30, 30));

		m_pGUIContext->EndGroup();

		m_pGUIContext->DrawRect(RgVec2(50, 70), RgVec2(50, 50));

		m_pGUIContext->EndGUI();


	}
	void EditorGUI::OnRender()
	{
		m_pBindGraphics->OnRender();
	}
}


