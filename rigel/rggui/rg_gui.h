#pragma once
#include "rggui.h"


namespace rg {
	class RgGUIContext;

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