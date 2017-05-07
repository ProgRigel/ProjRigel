#pragma once
#include "Stdafx.h"
#include "RigelEditorApp.h"
#include "cRigelGrphicsBackend.h"

namespace RigelCore
{
	ref class RigelEditorApp;

	class cRigelEditorApp
	{
	private:
		msclr::auto_gcroot<RigelEditorApp^> mClr;
		HWND hwndWin;
		WNDCLASSEX wc;

		cRigelGrphicsBackend *mGraphicBackend;

	private:


	public:
		cRigelEditorApp(RigelEditorApp^ clr);
		~cRigelEditorApp();

		void Create();
		void Run();

		void UpdateMsgProc();
		void Update();
		void Draw();
		void Render();
		void LateUpdate();

		static cRigelEditorApp *GetApp();

		LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParams, LPARAM lParams);

	public:
		static cRigelEditorApp *mInst;

	};
}



