#include "rgeditor_egui.h"
#include <imgui\imgui.h>
namespace rgeditor {

	RgEditorModuleEGUI* RgEditorModuleEGUI::m_pInstance = nullptr;

	void RgEditorModuleEGUI::init()
	{
	}
	void RgEditorModuleEGUI::shutdown()
	{

	}

	void RgEditorModuleEGUI::update(){

		drawEditorBasis();
		for (auto iter = m_vGUIFunction.begin(); iter != m_vGUIFunction.end(); iter++) {
			(*iter)();
		}

	}
	void RgEditorModuleEGUI::registerEGUIWindow(std::function<void()> guicallback)
	{
		m_pInstance->m_vGUIFunction.push_back(guicallback);
	}
	void RgEditorModuleEGUI::registerEGUIMenuItem(const char * category, const char * item , std::function<void()> guicallback)
	{
		auto& menuitems = m_pInstance->m_vMenuItems;
		auto iter = menuitems.find(category);
		if (iter == menuitems.end()) {
			menuitems.insert(std::make_pair(category, std::map<std::string, std::function<void()>>()));
		}
		auto& submenu = menuitems[category];
		auto subiter = submenu.find(item);
		if(subiter == submenu.end()){
			submenu.insert(std::make_pair(item, guicallback));
		}
		else
		{
			assert(false);
		}
	}
	void RgEditorModuleEGUI::drawEditorBasis()
	{
		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::BeginMenu("New")) {
					if(ImGui::MenuItem("Project")){}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Open")) {
					if (ImGui::MenuItem("Project")) {}
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}

			//registered menuitems
			for (auto iter = m_vMenuItems.begin(); iter != m_vMenuItems.end(); iter++) {

				if (ImGui::BeginMenu((*iter).first.c_str())) {
					auto& submenu = (*iter).second;
					for (auto siter = submenu.begin(); siter != submenu.end(); siter++) {
						if (ImGui::MenuItem((*siter).first.c_str())) (*siter).second();
					}
					ImGui::EndMenu();
				}
			}

			ImGui::EndMainMenuBar();
		}
	}
}


