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
		//ctx->GUIText("this is engine render result", rg::RgVec4(10, 10, 100, 20));
		if (ctx->GUIButton(rg::RgVec2::Zero, rg::RgVec2(100, 20), "Run", rg::RgGUIColors::Carrot)) {
			RgLogD() << "run engine";
		}

	}

}

