#include "stdafx.h"
#include "cRigelGuiUtil.h"
#include <imgui\imgui.h>

namespace RigelCore
{
	int ModalMessageBox(const char * title,const char * info)
	{
		int ret = 0;
		ImGui::OpenPopup(title);
		if (ImGui::BeginPopupModal(title, NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text(info);
			ImGui::Separator();

			if (ImGui::Button("Cancel",ImVec2(120,0)))
			{
				ImGui::CloseCurrentPopup();
				ret = 2;
			}
			ImGui::SameLine();
			if (ImGui::Button("OK", ImVec2(120, 0)))
			{
				ImGui::CloseCurrentPopup();
				ret = 1;
			}
			ImGui::EndPopup();
		}
		return ret;
	}
}