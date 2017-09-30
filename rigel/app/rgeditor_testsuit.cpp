#include "stdafx.h"
#include "rgeditor_testsuit.h"

namespace editor {
	RgEditorWindowTestSuit::RgEditorWindowTestSuit():RgEditorWindow()
	{
		m_guiwindow.title = "TestSuit";
		
	}
	RgEditorWindowTestSuit::~RgEditorWindowTestSuit()
	{
	}

	void RgEditorWindowTestSuit::OnGUI(rg::RgGUIContext * ctx)
	{
	}

}
