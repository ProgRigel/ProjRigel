#pragma once
#include "rgeditor_window.h"
namespace editor {
	class RgEditorWindowTestSuit : public RgEditorWindow {
	public:
		RgEditorWindowTestSuit();
		~RgEditorWindowTestSuit();

	protected:
		void OnGUI(rg::RgGUIContext * ctx);
	};
}