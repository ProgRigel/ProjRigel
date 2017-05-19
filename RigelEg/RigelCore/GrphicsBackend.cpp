#include "stdafx.h"
#include "GrphicsBackend.h"
#include "cImguiImplDX11.h"

#include <imgui\imgui.h>

// DirectX
#include <d3d11.h>
#include <d3dcompiler.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

namespace RigelCore
{

	GrphicsBackend::GrphicsBackend()
	{
		
	}


	GrphicsBackend::~GrphicsBackend()
	{
		CleanupRenderTarget();
		CleanupDeviceD3D();
	}

	HRESULT GrphicsBackend::CreateDeviceD3D(HWND hWnd)
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

	void GrphicsBackend::CreateRenderTarget()
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

	void GrphicsBackend::CleanupRenderTarget()
	{
		if (pMainRenderTargetView)
		{
			pMainRenderTargetView->Release();
			pMainRenderTargetView = NULL;
		}
	}

	void GrphicsBackend::CleanupDeviceD3D()
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
	void GrphicsBackend::onStart()
	{
		DebugLog("onStart");
		ImGui_ImplDX11_Init(hwndWin, pd3dDevice, pd3dDeviceContext);

	}
	void GrphicsBackend::PreRender()
	{
		//gui new frame
		ImGui_ImplDX11_NewFrame();

		pd3dDeviceContext->ClearRenderTargetView(pMainRenderTargetView, clearColor);
	}

	void GrphicsBackend::Render()
	{
		ImGui::ShowTestWindow();

		ImGui::Render();
	}

	void GrphicsBackend::Present()
	{
		pSwapChain->Present(0, 0);
	}

	LRESULT GrphicsBackend::ProcMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

	void GrphicsBackend::CreateTexture(const unsigned char * pixel, int width, int height)
	{
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Width = width;
		desc.Height = height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;

		ID3D11Texture2D *pTexture = nullptr;
		D3D11_SUBRESOURCE_DATA subResource;
		subResource.pSysMem = pixel;
		subResource.SysMemPitch = desc.Width * 4;
		subResource.SysMemSlicePitch = 0;

		pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);

		//SRV
		ID3D11ShaderResourceView *pSRV = nullptr;

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(srvDesc));
		srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = desc.MipLevels;
		srvDesc.Texture2D.MostDetailedMip = 0;
		pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, &pSRV);
		pTexture->Release();
	}
	
	void GrphicsBackend::onDestroy()
	{
		DebugLog("onDestroy");
		ImGui_ImplDX11_Shutdown();

		CleanupDeviceD3D();
	}

}