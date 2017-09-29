#pragma once
#include "rgeditor_window.h"
namespace editor {
	class RgEditorWindowTestSuit : public RgEditorWindow {
	public:
		RgEditorWindowTestSuit():RgEditorWindow(){}
		~RgEditorWindowTestSuit();

	protected:
		void OnGUI();
	};
}