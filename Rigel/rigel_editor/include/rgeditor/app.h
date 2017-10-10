#pragma once
#include <rgcore\rgcore.h>
#include <Windows.h>

#include <rgcore\rgcore.h>
#include <rgcore\rg_windowManager.h>
#include <rgcore\rg_module_font.h>
#include <rggraphics\rg_graphicsAPI.h>
#include <rggui\rg_gui.h>
#include <rggui\rg_gui_context.h>

#include "app_graphics.h"

using namespace rg;

namespace editor {

	class EditorGUI;

	class RigelApp {

	private:
		RgWindow *m_pWindow = nullptr;
		RigelAppGraphics * m_pAppGraphics = nullptr;
		EditorGUI * m_pEditorGUI = nullptr;

		RigelApp(const RigelApp&) = delete;
		RigelApp& operator=(const RigelApp&) = delete;
	public:
		RigelApp();
		~RigelApp();
	public:
		void Run();
		void onRegisterWindow();
		void onRender();

		RigelAppGraphics * GetGraphics() const;

		static RigelApp * GetInstance();
	private:
		static RigelApp* m_pInstance;

	};
}

