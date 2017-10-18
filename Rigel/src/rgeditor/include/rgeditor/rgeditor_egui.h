#pragma once
#include "rgeditor_module.h"
#include <functional>
#include <vector>
#include <map>
namespace rgeditor{


	class RgEditorEGUIWindow;

	class RgEditorModuleEGUI : public RgEditorModule
	{
	public:
		RgEditorModuleEGUI() :RgEditorModule(RgEditorBaseModuleType::EGUI) {

			m_pInstance = this;
		}

		void init();
		void shutdown();
		void update();

		static void registerEGUIWindow(std::function<void()> guicallback);
		static void registerEGUIMenuItem(const char* category, const char * item , std::function<void()> guicallback);


	private:
		RgEditorModuleEGUI(const RgEditorModuleEGUI&) = delete;
		RgEditorModuleEGUI& operator=(const RgEditorModuleEGUI&) = delete;

		static RgEditorModuleEGUI* m_pInstance;

		std::vector<std::function<void()>> m_vGUIFunction;
		std::map<std::string, std::map<std::string, std::function<void()>>> m_vMenuItems;

		void drawEditorBasis();
	};


	
}