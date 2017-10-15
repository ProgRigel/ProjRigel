#pragma once
#include "rgeditor_window.h"

namespace editor {
	class RgEditorEngineRunnerWindow : public RgEditorWindow {
	public:
		RgEditorEngineRunnerWindow();
		~RgEditorEngineRunnerWindow();

	protected:
		void OnGUI(rg::RgGUIContext * ctx);

		void EngineRun();
		void EnginePause();
		void EngineResume();
		void EngineStop();
	};
}