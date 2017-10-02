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

		ctx->GUIChar('R', rg::RgVec4(0, 0, 20, 20), rg::RgGUIColors::Carrot);
		ctx->GUIChar('A', rg::RgVec4(20, 0, 20, 20), rg::RgGUIColors::Carrot);
		ctx->GUIChar('W', rg::RgVec4(40, 0, 20, 20), rg::RgGUIColors::Carrot);
		ctx->GUIChar('E', rg::RgVec4(60, 0, 20, 20), rg::RgGUIColors::Carrot);
		ctx->GUIChar('D', rg::RgVec4(80, 0, 20, 20), rg::RgGUIColors::Carrot);
		ctx->GUIChar('W', rg::RgVec4(100, 0, 20, 20), rg::RgGUIColors::Carrot);
	}

}

