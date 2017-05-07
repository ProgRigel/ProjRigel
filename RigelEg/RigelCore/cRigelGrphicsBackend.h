#pragma once
#include "Stdafx.h"

#include <d3d11.h>

namespace RigelCore
{
	class cRigelGrphicsBackend
	{
	public:
		cRigelGrphicsBackend();
		~cRigelGrphicsBackend();

		HRESULT CreateDeviceD3D(HWND hWnd);
		void CreateRenderTarget();
		void CleanupRenderTarget();
		void CleanupDeviceD3D();

		void onStart();
		void onDestroy();

		void PreRender();
		void Render();
		void Present();
		
		LRESULT ProcMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		ID3D11Device* pd3dDevice = NULL;
		ID3D11DeviceContext* pd3dDeviceContext = NULL;
		IDXGISwapChain* pSwapChain = NULL;
		ID3D11RenderTargetView* pMainRenderTargetView = NULL;

		HWND hwndWin;

		const float* clearColor = new float[4]{ 0.2f, 0.2f, 0.2f, 1.0f };
	};

}

