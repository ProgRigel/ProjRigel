#pragma once
#include "rgeditor_window.h"

namespace editor {
	class RgEditorWindowDebugWindow : public RgEditorWindow {
	public:
		RgEditorWindowDebugWindow():RgEditorWindow(){}
		~RgEditorWindowDebugWindow();

	protected:
		void OnGUI();
	};
}