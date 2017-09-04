#include "rg_graphicsContextDX11.h"
#include <iostream>

namespace rg {
	RgGraphicsContextDX11::RgGraphicsContextDX11()
	{
		
	}
	RgGraphicsContextDX11::~RgGraphicsContextDX11()
	{
	}
	void RgGraphicsContextDX11::init()
	{
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
		IDXGIFactory * dxgifactory;
		HRESULT result = m_pD3D11Device->QueryInterface(__uuidof(IDXGIFactory), (void**)&dxgifactory);
		if (result == S_OK) {
			RgLogD() << "suc";
		}
		return result;
	}
}

