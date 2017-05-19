#pragma once
#include "Stdafx.h"
#include "RigelEditorApp.h"
#include "GrphicsBackend.h"

namespace RigelCore
{
	ref class RigelEditorApp;

	class EditorApp
	{
	private:
		msclr::auto_gcroot<RigelEditorApp^> mClr;
		HWND hwndWin;
		WNDCLASSEX wc;

		GrphicsBackend *mGraphicBackend;
	public:
		EditorApp(RigelEditorApp^ clr);
		~EditorApp();

		void Create();
		void Run();

		void UpdateMsgProc();
		void Update();
		void Draw();
		void Render();
		void LateUpdate();

		static EditorApp *GetApp();

		LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParams, LPARAM lParams);
	public:
		static EditorApp *mInst;

	};
}



