#include "rgeditor_module.h"

#include "rgeditor_egui.h"
#include <imgui\imgui.h>
#include <iostream>

namespace rgeditor {

	static std::vector<RgEditorModule*> g_vEditorModules;
	void rgEditorModuleInit()
	{
		g_vEditorModules.push_back(new RgEditorModuleEGUI());
		g_vEditorModules.push_back(new RgEditorModuleModuleManager());
		g_vEditorModules.push_back(new RgEditorModuleConsole());


		for (auto iter = g_vEditorModules.rbegin(); iter != g_vEditorModules.rend(); iter++) {
			(*iter)->init();
		}
	}

	void rgEditorModuleShutdown()
	{
		for (auto iter = g_vEditorModules.rbegin(); iter != g_vEditorModules.rend(); iter++) {
			(*iter)->shutdown();
			delete (*iter);
		}

		std::vector<RgEditorModule*>().swap(g_vEditorModules);
	}

	void rgEditorModuleUpdate()
	{
		for (auto iter = g_vEditorModules.begin(); iter != g_vEditorModules.end(); iter++) {
			(*iter)->update();
		}
	}


	RgEditorModule::RgEditorModule(RgEditorBaseModuleType _type)
	{
		m_type = _type;
	}

	void RgEditorModule::update()
	{

	}


#pragma region ModuleManager


	void RgEditorModuleModuleManager::init()
	{
		static bool m_bShowManager = false;
		RgEditorModuleEGUI::registerEGUIMenuItem("Tools", "ModuleManager", []() {
			m_bShowManager = true;

		});

		RgEditorModuleEGUI::registerEGUIWindow([]() {

			if (m_bShowManager) {
				if (ImGui::Begin("ModuleManager",&m_bShowManager)) {
					ImGui::Text("Hello %d", 10);
				}
				ImGui::End();
			}
			
		});
	}

	void RgEditorModuleModuleManager::shutdown()
	{

	}
#pragma endregion


#pragma region Console

	void RgEditorModuleConsole::init()
	{
		static bool m_bShowManager = false;
		RgEditorModuleEGUI::registerEGUIMenuItem("Tools", "Console", []() {
			m_bShowManager = true;
		});

		RgEditorModuleEGUI::registerEGUIWindow([]() {
			if (m_bShowManager) {
				ImGui::SetNextWindowSize(ImVec2(500.0f, 200.0f), ImGuiSetCond_FirstUseEver);
				if (ImGui::Begin("Console", &m_bShowManager)) {
					
				}
				ImGui::End();
			}

		});
	}

	void RgEditorModuleConsole::shutdown()
	{
	}
	void RgEditorModuleConsole::drawLogs()
	{
	}
#pragma endregion


	

}

