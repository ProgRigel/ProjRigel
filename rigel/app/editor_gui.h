#pragma once

namespace editor {

	class EditorGUI
	{
	public:
		EditorGUI() = default;
		~EditorGUI();

		void Release();

	private:
		EditorGUI(const EditorGUI&) = delete;
		EditorGUI& operator=(const EditorGUI&) = delete;
	};

}