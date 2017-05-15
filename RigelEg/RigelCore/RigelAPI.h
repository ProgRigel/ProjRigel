#pragma once
#include "Stdafx.h"
#include "RigelAPIgui.h"

using namespace System;

namespace RigelCore
{
	public ref class RigelAPI abstract sealed
	{
	public:

		static void Test();
		static void TestParam(String^ info);


	//Editor GUI
	public:
		//const
		static bool *CST_OPEN = new bool(true);
		static bool *CST_CLOSE = new bool(false);


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

		static void SameLine();

		//window
		static bool Begin(String ^name);
		static bool Begin(String ^name, int wid);
		static void End();

	//EditorGUI Util
	public:
		static void InitEGUI();
		static int EGUI_registerWindow(int wind);
		static void EGUI_unregisterWindow(int wind);
		static void EGUI_loadTTF(String^ file);
	private:
		static std::map<int,cEGUIwin*>* EGUI_mWindowState;
	};

}


