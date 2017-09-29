#include "stdafx.h"
#include "rgeditor_window.h"


namespace editor {
	RgEditorWindow::RgEditorWindow()
	{
		m_guiwindow.windowrect.z = 400;
		m_guiwindow.windowrect.w = 300;
	}
	RgEditorWindow::~RgEditorWindow()
	{
	}
	void RgEditorWindow::InternalOnGUI(rg::RgGUIContext* ctx)
	{
		if (ctx->GUIWindowBegin(m_guiwindow)) {
			this->OnGUI(ctx);
		}
		ctx->GUIWindowEnd();
	}
}


