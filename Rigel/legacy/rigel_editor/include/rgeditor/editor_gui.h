#pragma once
#include <rggraphics\rg_graphicscontext.h>
#include <rggui\rg_gui_bind_graphics.h>
#include <rggui\rg_gui_context.h>
#include <rgcore\rg_window.h>

namespace editor {

	class EditorGUI
	{
	public:
		EditorGUI();
		~EditorGUI();

		void Release();

		void BindGraphics(rg::RgGraphicsContext * graphicsCtx);

		void OnWindowGUI(const rg::RgWindowEvent e);
		void OnRender();

	private:
		EditorGUI(const EditorGUI&) = delete;
		EditorGUI& operator=(const EditorGUI&) = delete;

		rg::RgGUIContext * m_pGUIContext = nullptr;
		rg::RgGUIBindGraphics * m_pBindGraphics = nullptr;
	};

}