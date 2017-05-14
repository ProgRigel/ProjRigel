#include "stdafx.h"
#include "RigelAPI.h"
#include <imgui\imgui.h>
#include "cRigelGuiUtil.h"
using namespace msclr::interop;
using namespace std;

namespace RigelCore
{
	void RigelAPI::Test()
	{
		if (ImGui::TreeNode("tree"))
		{
			if (ImGui::TreeNode("tree1"))
			{
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("tree2"))
			{
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("tree3"))
			{
				if (ImGui::TreeNode("tree4"))
				{
					ImGui::TreePop();
				}
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}
	}
	void RigelAPI::TestParam(String ^ info)
	{
		std::cout << "test param" << std::endl;
	}



#pragma region EdtiroGUI
	bool RigelAPI::BeginMainMenuBar()
	{
		return ImGui::BeginMainMenuBar();
	}

	void RigelAPI::EndMainMenuBar()
	{
		ImGui::EndMainMenuBar();
	}

	bool RigelAPI::BeginMenu(String^ label)
	{
		string clabel = marshal_as<string>(label);
		return ImGui::BeginMenu(clabel.c_str());
	}

	void RigelAPI::EndMenu()
	{
		ImGui::EndMenu();
	}

	bool RigelAPI::MenuItem(String ^ label)
	{
		string clabel = marshal_as<string>(label);
		return ImGui::MenuItem(clabel.c_str());
	}

	void RigelAPI::Text(String ^ text)
	{
		std::string cstr = marshal_as<std::string>(text);
		ImGui::Text(cstr.c_str());
	}

	void RigelAPI::TextColored(String ^ text, float r, float g, float b, float a)
	{
		std::string cstr = marshal_as<std::string>(text);
		ImVec4 color(r, g, b, a);
		ImGui::TextColored(color, cstr.c_str());
	}

	void RigelAPI::TextDisabled(String ^ text)
	{
		std::string cstr = marshal_as<std::string>(text);
		ImGui::TextDisabled(cstr.c_str());
	}

	void RigelAPI::TextWrapped(String ^ text)
	{
		std::string cstr = marshal_as<std::string>(text);
		ImGui::TextWrapped(cstr.c_str());
	}

	void RigelAPI::LabelText(String ^ label, String ^ text)
	{
		std::string ctext = marshal_as<std::string>(text);
		std::string clabel = marshal_as<std::string>(label);
		ImGui::LabelText(clabel.c_str(), ctext.c_str());
	}

	void RigelAPI::Bullet()
	{
		ImGui::Bullet();
	}

	void RigelAPI::BulletText(String ^ text)
	{
		std::string cstr = marshal_as<std::string>(text);
		ImGui::BulletText(cstr.c_str());
	}

	bool RigelAPI::Button(String ^ label)
	{
		std::string clabel = marshal_as<std::string>(label);
		return ImGui::Button(clabel.c_str());
	}

	bool RigelAPI::Button(String ^ label, float w, float h)
	{
		std::string clabel = marshal_as<std::string>(label);
		ImVec2 size(w, h);
		return ImGui::Button(clabel.c_str(), size);
	}

	bool RigelAPI::SmallButton(String ^ label)
	{
		string clabel = marshal_as<string>(label);
		return ImGui::SmallButton(clabel.c_str());
	}

	void RigelAPI::SetTooltip(String ^ text)
	{
		string ctext = marshal_as<string>(text);
		ImGui::SetTooltip(ctext.c_str());
	}

	void RigelAPI::BeginTooltip()
	{
		ImGui::BeginTooltip();
	}

	void RigelAPI::EndTooltip()
	{
		ImGui::EndTooltip();
	}

	bool RigelAPI::IsItemHovered()
	{
		return ImGui::IsItemHovered();
	}

	bool RigelAPI::IsItemHoveredRect()
	{
		return ImGui::IsItemHoveredRect();
	}

	bool RigelAPI::IsItemClicked(int mouseButton)
	{
		return ImGui::IsItemClicked(mouseButton);
	}

	int RigelAPI::ModalMessageBox(String ^ title, String ^ info)
	{
		string ctitle = marshal_as<string>(title);
		string cinfo = marshal_as<string>(info);
		return RigelCore::ModalMessageBox(ctitle.c_str(), cinfo.c_str());
	}

	bool RigelAPI::ModelMessageTip(String ^ title, String ^ info)
	{
		const char *ctitle = marshal_as<string>(title).c_str();
		const char *cinfo = marshal_as<string>(info).c_str();
		return RigelCore::ModalMessageTip(ctitle, cinfo);
	}

	void RigelAPI::SameLine()
	{
		ImGui::SameLine();
	}

	bool RigelAPI::Begin(String ^ name)
	{
		std::string cname = marshal_as<string>(name);
		return ImGui::Begin(cname.c_str(), CST_OPEN);
	}

	bool RigelAPI::Begin(String ^ name, int wid)
	{
		std::string cname = marshal_as<string>(name);
		return ImGui::Begin(cname.c_str(), &((*EGUI_mWindowState)[wid]->open));
	}

	void RigelAPI::End()
	{
		ImGui::End();
	}


#pragma endregion

	void RigelAPI::InitEGUI()
	{
		EGUI_mWindowState = new map<int, cEGUIwin*>();
	}

	int RigelAPI::EGUI_registerWindow(int wid)
	{
		if (EGUI_mWindowState->count(wid) > 0)
		{
			return wid;
		}
		else
		{
			cEGUIwin *tempwin = new cEGUIwin();
			EGUI_mWindowState->insert(make_pair((int)tempwin,tempwin));
			return (int)tempwin;
		}
	}

	void RigelAPI::EGUI_unregisterWindow(int wind)
	{
		if(EGUI_mWindowState->count(wind) >0)
			EGUI_mWindowState->erase(wind);
	}


}
