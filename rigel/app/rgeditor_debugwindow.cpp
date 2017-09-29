#include "stdafx.h"
#include "rgeditor_debugwindow.h"

namespace editor {
	RgEditorWindowDebugWindow::RgEditorWindowDebugWindow():RgEditorWindow()
	{
		m_guiwindow.title = "DebugWindow";
		m_guiwindow.windowrect.setxy(rg::RgVec2(200, 100));
	}
	RgEditorWindowDebugWindow::~RgEditorWindowDebugWindow()
	{
	}

	void RgEditorWindowDebugWindow::OnGUI(rg::RgGUIContext * ctx)
	{
		RgLogD() << "debugwindow update";
	}

}

