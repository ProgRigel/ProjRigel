#pragma once
#include <rgcore\rgcore.h>
#include "rg_gui_context.h"
#include <vector>

namespace rg {

	class RgGUI
	{
	public:
		static bool CreateRgGUIContext(RgGUIContext** pguictx);
		static void Release();
	private:
		static std::vector<RgGUIContext*> m_vGuiContexts;

	private:
		RgGUI() = default;
		~RgGUI();

		RgGUI(const RgGUI&) = delete;
		RgGUI& operator=(const RgGUI&) = delete;
	};

}