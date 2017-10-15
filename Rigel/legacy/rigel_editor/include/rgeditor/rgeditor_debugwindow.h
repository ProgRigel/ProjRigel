#pragma once
#include "rgeditor_window.h"

namespace editor {
	class RgEditorWindowDebugWindow : public RgEditorWindow {
	public:
		RgEditorWindowDebugWindow();
		~RgEditorWindowDebugWindow();

	protected:
		void OnGUI(rg::RgGUIContext * ctx);
	};
}