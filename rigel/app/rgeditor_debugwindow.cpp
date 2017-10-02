#include "stdafx.h"
#include "rgeditor_debugwindow.h"
#include <rggui\rg_gui_style.h>

namespace editor {
	RgEditorWindowDebugWindow::RgEditorWindowDebugWindow():RgEditorWindow()
	{
		m_guiwindow.title = "DebugWindow";
		m_guiwindow.windowrect.setxy(rg::RgVec2(200, 100));
		m_guiwindow.windowColor = rg::RgGUIColors::Emerald;
	}
	RgEditorWindowDebugWindow::~RgEditorWindowDebugWindow()
	{
	}

	void RgEditorWindowDebugWindow::OnGUI(rg::RgGUIContext * ctx)
	{
		ctx->GUIRect(rg::RgVec2(10,10), rg::RgVec2(120, 120), rg::RgGUIColors::MidnightBlue);
	}

}

