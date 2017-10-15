#include "stdafx.h"
#include "editor_gui.h"
#include <rggui\rg_gui.h>
#include <rggui\rg_gui_bind_graphics.h>
#include <rggui\rg_gui_context.h>
#include "rgeditor_window.h"
#include "rgeditor_testsuit.h"
#include "rgeditor_debugwindow.h"
#include "rgeditor_enginerunner.h"

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


		static bool tst = true;
		if (tst) {
			tst = false;

		}

		static RgEditorWindowTestSuit testsuitwindow;
		static RgEditorWindowDebugWindow debugwindow;
		static RgEditorEngineRunnerWindow engineRunnerWindow;

		ctx->GUIBegin(e);

		testsuitwindow.InternalOnGUI(ctx);
		debugwindow.InternalOnGUI(ctx);
		engineRunnerWindow.InternalOnGUI(ctx);

		ctx->GUIEnd();

	}
	void EditorGUI::OnRender()
	{
		m_pBindGraphics->OnRender();
	}
}


