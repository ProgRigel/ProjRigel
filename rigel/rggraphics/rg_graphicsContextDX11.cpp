#include "rg_graphicsContextDX11.h"
#include <iostream>

namespace rg {
	RgGraphicsContextDX11::RgGraphicsContextDX11()
	{
		
	}
	RgGraphicsContextDX11::~RgGraphicsContextDX11()
	{
	}
	void RgGraphicsContextDX11::init(RG_GRAPHICS_INIT_SETTINGS *settings)
	{
		m_settings = *settings;

		std::cout << "init dx11 api" << std::endl;
		createDeviceAndContext();
		createSwapChain();
	}

	void RgGraphicsContextDX11::release()
	{
		std::cout << "release dx11 api" << std::endl;

		releaseDeviceAndContext();
	}
	HRESULT RgGraphicsContextDX11::createDeviceAndContext()
	{
		D3D_FEATURE_LEVEL featureLevel;
		CONST D3D_FEATURE_LEVEL featureLevelArray[1] = {
			D3D_FEATURE_LEVEL_11_0 };
		HRESULT result = D3D11CreateDevice(
			NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			0,
			featureLevelArray,
			1,
			D3D11_SDK_VERSION,
			&m_pD3D11Device,
			&featureLevel,
			&m_pD3D11DeviceContext
		);
		if (result != S_OK) {
			RgLogD() << "create dx11 device fail";
			return E_FAIL;
		}
		return S_OK;
	}
	void RgGraphicsContextDX11::releaseDeviceAndContext()
	{
		if (m_pD3D11DeviceContext) {
			m_pD3D11DeviceContext->Release();
			m_pD3D11DeviceContext = nullptr;
		}
		if (m_pD3D11Device) {
			m_pD3D11Device->Release();
			m_pD3D11Device = nullptr;
		}
			
	}
	HRESULT RgGraphicsContextDX11::createSwapChain()
	{
		IDXGIDevice * pDXGIDevice = nullptr;
		HRESULT result = m_pD3D11Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&pDXGIDevice);
		if (result != S_OK) {
			RgLogE() << GetLastError();
		}
		IDXGIAdapter * pDXGIAdapter = nullptr;
		result = pDXGIDevice->GetAdapter(&pDXGIAdapter);
		if (result != S_OK) {
			RgLogE() << GetLastError();
		}

		IDXGIFactory * pIDXGIFactory = nullptr;
		result =  pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pIDXGIFactory);
		if (result != S_OK) {
			RgLogE() << GetLastError();
		}

		DXGI_SWAP_CHAIN_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.BufferCount = 2;
		desc.BufferDesc.Width = m_settings.BufferWidth;
		desc.BufferDesc.Height = m_settings.BufferHeight;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.OutputWindow = nullptr;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Windowed = true;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;


		result = pIDXGIFactory->CreateSwapChain(m_pD3D11Device, &desc,&m_pSwapChain);


		return result;
	}
}

