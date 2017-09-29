#pragma once
#include <rggui\rg_gui_context.h>
namespace editor {
	class EditorGUI;

	class RgEditorWindow {
	public:
		RgEditorWindow();
		virtual ~RgEditorWindow();

	protected:
		virtual void OnGUI();

	private:
		RgEditorWindow(const RgEditorWindow&) = delete;
		RgEditorWindow& operator=(const RgEditorWindow&) = delete;

		void InternalOnGUI();

		friend class EditorGUI;
	};

}