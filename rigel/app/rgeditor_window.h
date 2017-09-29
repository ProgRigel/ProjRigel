#pragma once
#include <rggui\rg_gui_context.h>
namespace editor {
	class EditorGUI;
	class rg::RgGUIContext;

	class RgEditorWindow {
	public:
		RgEditorWindow();
		virtual ~RgEditorWindow();

	protected:
		virtual void OnGUI();

	private:
		RgEditorWindow(const RgEditorWindow&) = delete;
		RgEditorWindow& operator=(const RgEditorWindow&) = delete;

		void InternalOnGUI(rg::RgGUIContext* ctx);

		friend class EditorGUI;
	};

}