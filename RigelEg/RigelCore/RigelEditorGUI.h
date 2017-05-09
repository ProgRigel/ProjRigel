#pragma once
using namespace System;
using namespace msclr::interop;
using namespace std;

namespace RigelCore
{
	//API for .net
	//CLI/C++ or C#
	public ref class RigelEditorGUI abstract sealed
	{
	public:

		//menu
		static bool BeginMainMenuBar();
		static void EndMainMenuBar();
		static bool BeginMenu(String ^label);
		static void EndMenu();
		static bool MenuItem(String ^label);

		//Main


		static void Text(String ^text);
		static void TextColored(String ^text, float r, float g, float b, float a);
		static void TextDisabled(String ^text);
		static void TextWrapped(String ^text);

		static void LabelText(String ^label, String ^text);

		static void Bullet();
		static void BulletText(String ^text);

		static bool Button(String ^label);
		static bool Button(String ^label, float w, float h);
		static bool SmallButton(String ^label);


		//tooltip
		static void SetTooltip(String ^text);
		static void BeginTooltip();
		static void EndTooltip();

		//utility
		static bool IsItemHovered();
		static bool IsItemHoveredRect();
		static bool IsItemClicked(int mouseButton);


		//util
		static int ModalMessageBox(String ^title, String ^info);
		static bool ModelMessageTip(String ^title, String ^info);

	};

}
