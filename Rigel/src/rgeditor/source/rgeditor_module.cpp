#include "rgeditor.h"
#include "rgeditor_module.h"

#include "rgeditor_egui.h"
#include <imgui\imgui.h>
#include <iostream>

namespace rgeditor {

	static std::vector<RgEditorModule*> g_vEditorModules;
	void rgEditorModuleInit()
	{
		g_vEditorModules.push_back(new RgEditorModuleEGUI());
		g_vEditorModules.push_back(new RgEditorModuleConsole());
		g_vEditorModules.push_back(new RgEditorModuleModuleManager());
		


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

	RgEditorModuleConsole* RgEditorModuleConsole::m_pInstance = nullptr;

	void RgEditorModuleConsole::init()
	{
		static bool m_bShowManager = true;
		RgEditorModuleEGUI::registerEGUIMenuItem("Tools", "Console", []() {
			m_bShowManager = true;
			RGLOG_DEBUG("open ModuleConsole");
		});

		RgEditorModuleEGUI::registerEGUIWindow([this]() {
			if (m_bShowManager) {
				ImGui::SetNextWindowSize(ImVec2(500.0f, 200.0f), ImGuiSetCond_FirstUseEver);
				if (ImGui::Begin("Console", &m_bShowManager,ImGuiWindowFlags_MenuBar)) {
					

					drawMenubar();
					

					drawLogs();
				}
				ImGui::End();
			}

		});


		m_logdeque.push_back("1dwasdw");
		m_logdeque.push_back("1=----dwasddww");
		m_logdeque.push_back("---1dwasdw");
		m_logdeque.push_back("---1dwasdw");
	}

	void RgEditorModuleConsole::shutdown()
	{
	}
	void RgEditorModuleConsole::logDebug(const char * msg)
	{
		if (m_pInstance == nullptr) return;
		m_pInstance->m_logdeque.push_back(msg);
	}

	void RgEditorModuleConsole::logDebug(std::string msg)
	{
		if (m_pInstance == nullptr) return;
		m_pInstance->m_logdeque.push_back(msg);
	}

	void RgEditorModuleConsole::drawLogs()
	{
		for (auto iter = m_logdeque.begin(); iter != m_logdeque.end(); iter++) {
			ImGui::Text((*iter).c_str());
		}
	}
	void RgEditorModuleConsole::drawMenubar()
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::Button("Clear")) { m_logdeque.clear(); }
			if (ImGui::Button("Test")) { m_logdeque.push_back("test"); }

			ImGui::EndMenuBar();
		}
	}
#pragma endregion


	

}

