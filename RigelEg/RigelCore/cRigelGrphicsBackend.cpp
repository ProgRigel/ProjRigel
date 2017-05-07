#include "stdafx.h"
#include "cRigelGrphicsBackend.h"
#include "cImguiImplDX11.h"

#include <imgui\imgui.h>

// DirectX
#include <d3d11.h>
#include <d3dcompiler.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

namespace RigelCore
{

	cRigelGrphicsBackend::cRigelGrphicsBackend()
	{
	}


	cRigelGrphicsBackend::~cRigelGrphicsBackend()
	{
	}

	HRESULT cRigelGrphicsBackend::CreateDeviceD3D(HWND hWnd)
	{
		hwndWin = hWnd;

		DXGI_SWAP_CHAIN_DESC sd;
		{
			ZeroMemory(&sd, sizeof(sd));
			sd.BufferCount = 2;
			sd.BufferDesc.Width = 0;
			sd.BufferDesc.Height = 0;
			sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			sd.BufferDesc.RefreshRate.Numerator = 60;
			sd.BufferDesc.RefreshRate.Denominator = 1;
			sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
			sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			sd.OutputWindow = hWnd;
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
			sd.Windowed = TRUE;
			sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		}

		UINT createDeviceFlags = 0;
		D3D_FEATURE_LEVEL featureLevel;
		const D3D_FEATURE_LEVEL featureLevelArray[1] = { D3D_FEATURE_LEVEL_11_0, };

		if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 1, D3D11_SDK_VERSION, &sd, &pSwapChain, &pd3dDevice, &featureLevel, &pd3dDeviceContext) != S_OK)
		{
			std::cout << "dx11 create device failed!" << std::endl;
			return E_FAIL;
		}
		CreateRenderTarget();
		return S_OK;
	}

	void cRigelGrphicsBackend::CreateRenderTarget()
	{
		DXGI_SWAP_CHAIN_DESC sd;
		pSwapChain->GetDesc(&sd);

		//create rendertarget
		ID3D11Texture2D* pBackBuffer;
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
		ZeroMemory(&renderTargetViewDesc, sizeof(renderTargetViewDesc));
		renderTargetViewDesc.Format = sd.BufferDesc.Format;
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		pd3dDevice->CreateRenderTargetView(pBackBuffer, &renderTargetViewDesc, &pMainRenderTargetView);
		pd3dDeviceContext->OMSetRenderTargets(1, &pMainRenderTargetView, NULL);
		pBackBuffer->Release();
	}

	void cRigelGrphicsBackend::CleanupRenderTarget()
	{
		if (pMainRenderTargetView)
		{
			pMainRenderTargetView->Release();
			pMainRenderTargetView = NULL;
		}
	}

	void cRigelGrphicsBackend::CleanupDeviceD3D()
	{
		CleanupRenderTarget();
		if (pSwapChain)pSwapChain->Release(); pSwapChain = NULL;
		if (pd3dDeviceContext)
		{
			pd3dDeviceContext->Release(); pd3dDeviceContext = NULL;
		}
		if (pd3dDevice)
		{
			pd3dDevice->Release();
			pd3dDevice = NULL;
		}
	}
	void cRigelGrphicsBackend::onStart()
	{
		DebugLog("onStart");
		ImGui_ImplDX11_Init(hwndWin, pd3dDevice, pd3dDeviceContext);
	}
	void cRigelGrphicsBackend::PreRender()
	{
		//gui new frame
		ImGui_ImplDX11_NewFrame();

		pd3dDeviceContext->ClearRenderTargetView(pMainRenderTargetView, clearColor);
	}

	void cRigelGrphicsBackend::Render()
	{
		ImGui::Render();
	}

	void cRigelGrphicsBackend::Present()
	{
		pSwapChain->Present(0, 0);
	}

	LRESULT cRigelGrphicsBackend::ProcMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (ImGui_ImplDX11_WndProcHandler(hWnd, msg, wParam, lParam))
			return true;
		switch(msg)
		{
		case WM_SIZE:
			if (pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
			{
				DebugLog("DX resize");
				ImGui_ImplDX11_InvalidateDeviceObjects();
				CleanupRenderTarget();
				pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
				CreateRenderTarget();
				ImGui_ImplDX11_CreateDeviceObjects();
			}
			return 0;
		case WM_SYSCOMMAND:
			if ((wParam & 0xfff0) == SC_KEYMENU)
				return 0;
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	
	void cRigelGrphicsBackend::onDestroy()
	{
		DebugLog("onDestroy");
		ImGui_ImplDX11_Shutdown();

		CleanupDeviceD3D();
	}
}