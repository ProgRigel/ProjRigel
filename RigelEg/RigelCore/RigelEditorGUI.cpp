#include "stdafx.h"
#include "RigelEditorGUI.h"
#include <imgui\imgui.h>
#include "cRigelGuiUtil.h"


bool RigelCore::RigelEditorGUI::BeginMainMenuBar()
{
	return ImGui::BeginMainMenuBar();
}

void RigelCore::RigelEditorGUI::EndMainMenuBar()
{
	ImGui::EndMainMenuBar();
}

bool RigelCore::RigelEditorGUI::BeginMenu(String^ label)
{
	string clabel = marshal_as<string>(label);
	return ImGui::BeginMenu(clabel.c_str());
}

void RigelCore::RigelEditorGUI::EndMenu()
{
	ImGui::EndMenu();
}

bool RigelCore::RigelEditorGUI::MenuItem(String ^ label)
{
	string clabel = marshal_as<string>(label);
	return ImGui::MenuItem(clabel.c_str());
}

void RigelCore::RigelEditorGUI::Text(String ^ text)
{
	std::string cstr = marshal_as<std::string>(text);
	ImGui::Text(cstr.c_str());
}

void RigelCore::RigelEditorGUI::TextColored(String ^ text, float r, float g, float b, float a)
{
	std::string cstr = marshal_as<std::string>(text);
	//std::cout<<r<<g<<b<<a<<std::endl;
	ImVec4 color(r,g,b,a);
	ImGui::TextColored(color, cstr.c_str());
}

void RigelCore::RigelEditorGUI::TextDisabled(String ^ text)
{
	std::string cstr = marshal_as<std::string>(text);
	ImGui::TextDisabled(cstr.c_str());
}

void RigelCore::RigelEditorGUI::TextWrapped(String ^ text)
{
	std::string cstr = marshal_as<std::string>(text);
	ImGui::TextWrapped(cstr.c_str());
}

void RigelCore::RigelEditorGUI::LabelText(String ^ label, String ^ text)
{
	std::string ctext = marshal_as<std::string>(text);
	std::string clabel = marshal_as<std::string>(label);
	ImGui::LabelText(clabel.c_str(),ctext.c_str());
}

void RigelCore::RigelEditorGUI::Bullet()
{
	ImGui::Bullet();
}

void RigelCore::RigelEditorGUI::BulletText(String ^ text)
{
	std::string cstr = marshal_as<std::string>(text);
	ImGui::BulletText(cstr.c_str());
}

bool RigelCore::RigelEditorGUI::Button(String ^ label)
{
	std::string clabel = marshal_as<std::string>(label);
	return ImGui::Button(clabel.c_str());
}

bool RigelCore::RigelEditorGUI::Button(String ^ label, float w, float h)
{
	std::string clabel = marshal_as<std::string>(label);
	ImVec2 size(w, h);
	return ImGui::Button(clabel.c_str(),size);
}

bool RigelCore::RigelEditorGUI::SmallButton(String ^ label)
{
	string clabel = marshal_as<string>(label);
	return ImGui::SmallButton(clabel.c_str());
}

void RigelCore::RigelEditorGUI::SetTooltip(String ^ text)
{
	string ctext = marshal_as<string>(text);
	ImGui::SetTooltip(ctext.c_str());
}

void RigelCore::RigelEditorGUI::BeginTooltip()
{
	ImGui::BeginTooltip();
}

void RigelCore::RigelEditorGUI::EndTooltip()
{
	ImGui::EndTooltip();
}

bool RigelCore::RigelEditorGUI::IsItemHovered()
{
	return ImGui::IsItemHovered();
}

bool RigelCore::RigelEditorGUI::IsItemHoveredRect()
{
	return ImGui::IsItemHoveredRect();
}

bool RigelCore::RigelEditorGUI::IsItemClicked(int mouseButton)
{
	return ImGui::IsItemClicked(mouseButton);
}

bool RigelCore::RigelEditorGUI::ModalMessageBox(String ^ title, String ^ info)
{
	string ctitle = marshal_as<string>(title);
	string cinfo = marshal_as<string>(info);
	return RigelCore::ModalMessageBox(ctitle.c_str(), cinfo.c_str());
}
