#pragma once
#include "Stdafx.h"
#include "EditorApp.h"

namespace RigelCore
{
	class EditorApp;

	public ref class RigelEditorApp
	{
	public:
		delegate void DelEvent();
		event DelEvent ^delOnGUI;

	private:
		EditorApp *_app;

	public:
		RigelEditorApp();
		~RigelEditorApp();

		void Run();
		void onWindowDestroy();

		void callbackOnGUI();
	};

}

