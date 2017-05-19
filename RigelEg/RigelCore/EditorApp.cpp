#include "Stdafx.h"
#include "EditorApp.h"

namespace RigelCore
{
	EditorApp * EditorApp::mInst;

	LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return EditorApp::GetApp()->MsgProc(hWnd,msg,wParam,lParam);
	}


	EditorApp::EditorApp(RigelEditorApp^ clr)
	{
		DebugLog("Init NativeEditorApp");
		mClr = clr;

		mInst = this;
	}

	EditorApp::~EditorApp()
	{
		DebugLog("deconstruct EditorApp");
		
		delete mGraphicBackend;
		mGraphicBackend = 0;

		//class
		DebugLog("unregister windowClass");
		UnregisterClass(_T("RigelEditorWinClass"), wc.hInstance);
	}

	void EditorApp::Create()
	{
		// winapi window
		wc = {
			sizeof(WNDCLASSEX),
			CS_CLASSDC,
			WndProc,
			0L,0L,
			GetModuleHandle(NULL),
			NULL,
			LoadCursor(NULL,IDC_ARROW),
			NULL,NULL,
			_T("RigelEditorWinClass"),NULL
		};

		RegisterClassEx(&wc);

		hwndWin = CreateWindow(_T("RigelEditorWinClass"), _T("RigelEditorWinClass"), WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

		//init directx
		mGraphicBackend = new GrphicsBackend();
		if (mGraphicBackend->CreateDeviceD3D(hwndWin) < 0)
		{
			mGraphicBackend->CleanupDeviceD3D();
			DebugLog("init directX failed");
			UnregisterClass(_T("RigelEditorWinClass"), wc.hInstance);
			return;
		}

		DebugLog("ShowWindow");
		ShowWindow(hwndWin, SW_SHOWDEFAULT);
		UpdateWindow(hwndWin);

		mGraphicBackend->onStart();

	}


	void EditorApp::Update()
	{

	}

	void EditorApp::Run()
	{
		DebugLog("cEditorApp Run");

		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		while (msg.message !=WM_QUIT)
		{
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				continue;
			}
			mGraphicBackend->PreRender();

			mClr->callbackOnGUI();

			mGraphicBackend->Render();
			mGraphicBackend->Present();

			System::Threading::Thread::Sleep(17);

		}
		mGraphicBackend->onDestroy();
		DebugLog("end runloop");
		
		mClr->onWindowDestroy();
	}

	EditorApp * EditorApp::GetApp()
	{
		return mInst;
	}

	LRESULT EditorApp::MsgProc(HWND hwnd, UINT msg, WPARAM wParams, LPARAM lParams)
	{
		if (mGraphicBackend->ProcMsg(hwnd, msg, wParams, lParams) == 0)
			return 0;
		return DefWindowProc(hwnd, msg, wParams, lParams);

	}

}

