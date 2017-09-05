#pragma once
#include "rg_graphicscontext.h"

#include <rgcore\rgcore.h>

#include <d3d11.h>
#include <dxgi.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dxguid.lib")


namespace rg {


	class RgGraphicsContextDX11 : public RgGraphicsContext
	{
	protected:
		RgGraphicsContextDX11();
		~RgGraphicsContextDX11();

		void init(RG_GRAPHICS_INIT_SETTINGS *settings);
		void release();

	public:
		void createBuffer();
		void createShader();
		void createSampleState();
		void createTexture();
		void createResourceView();
		void createLayout();

		void resizeBuffer(unsigned int width, unsigned int height);


	private:
		

		ID3D11Device *m_pD3D11Device = nullptr;
		ID3D11DeviceContext *m_pD3D11DeviceContext = nullptr;
		IDXGISwapChain * m_pSwapChain = nullptr;
		
		ID3D11RenderTargetView* m_pRenderTargetView = nullptr;

		HRESULT createDeviceAndContext();
		void releaseDeviceAndContext();
		HRESULT createSwapChain();

		HRESULT createRenderTarget();
		HRESULT clearRenderTarget();


	public:
		friend class RgGraphicsAPI;

	};
}