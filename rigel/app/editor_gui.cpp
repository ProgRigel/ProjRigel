#include "stdafx.h"
#include "editor_gui.h"
#include <rggui\rg_gui.h>
#include <rggui\rg_gui_bind_graphics.h>

#include "rgeditor_window.h"
#include "rgeditor_testsuit.h"
#include "rgeditor_debugwindow.h"

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

		static RgEditorWindowTestSuit testsuitwindow;
		static RgEditorWindowDebugWindow debugwindow;

		ctx->BeginGUI(e);

		testsuitwindow.InternalOnGUI();
		debugwindow.InternalOnGUI();

		ctx->EndGUI();

	}
	void EditorGUI::OnRender()
	{
		m_pBindGraphics->OnRender();
	}
}


