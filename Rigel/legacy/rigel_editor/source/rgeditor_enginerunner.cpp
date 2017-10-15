#include "stdafx.h"
#include "rgeditor_enginerunner.h"

namespace editor {
	RgEditorEngineRunnerWindow::RgEditorEngineRunnerWindow()
	{
		m_guiwindow.title = "RigelEngine";
		m_guiwindow.windowrect = rg::RgVec4(100, 50, 400, 300);
	}
	RgEditorEngineRunnerWindow::~RgEditorEngineRunnerWindow()
	{
	}
	void RgEditorEngineRunnerWindow::OnGUI(rg::RgGUIContext * ctx)
	{
		if (ctx->GUIButton(rg::RgVec2::Zero, rg::RgVec2(50, 20), "Run", rg::RgGUIColors::GreenSea)) {
			RgLogD() << "run engine";
		}

		if (ctx->GUIButton(rg::RgVec2(50,0), rg::RgVec2(50, 20), "Stop", rg::RgGUIColors::Emerald)) {
			RgLogD() << "stop engine";
		}
	}

}

