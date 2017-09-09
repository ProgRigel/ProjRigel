#include "rg_graphicsContextDX11.h"
#include <iostream>
#include "rg_shaderDX11.h"
#include "rg_bufferDX11.h"
#include "rg_render_context_dx11.h"
#include "rg_inputlayout.h"
#define HR_CEHCK(hr) if(hr != S_OK){RgLogE()<<GetLastError();}

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
		createRenderTarget();

		//set rendercontext
		auto renderctx = new RgRenderContextDX11();
		renderctx->m_pDeviceContext = m_pD3D11DeviceContext;
		m_pRenderContext = renderctx;
	}

	void RgGraphicsContextDX11::release()
	{
		std::cout << "release dx11 api" << std::endl;

		clearRenderTarget();
		releaseSwapChain();
		releaseDeviceAndContext();
	}
	void RgGraphicsContextDX11::DrawSetBuffer(std::shared_ptr<RgBuffer> buffer)
	{
	}
	void RgGraphicsContextDX11::DrawSetMaterial(std::shared_ptr<RgMaterial> material)
	{
	}
	void RgGraphicsContextDX11::DrawSetShader(std::shared_ptr<RgShader> shader)
	{
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
		if (m_pSwapChain) {
			m_pSwapChain->Release();
			m_pSwapChain = nullptr;
		}

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


		RgLogD() << m_settings.BufferWidth << m_settings.BufferHeight;

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
		desc.OutputWindow = m_settings.OutputWindow;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Windowed = true;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;


		result = pIDXGIFactory->CreateSwapChain(m_pD3D11Device, &desc,&m_pSwapChain);
		if (result != S_OK) {
			RgLogE() << GetLastError();
		}

		pDXGIDevice->Release();
		pDXGIDevice = nullptr;
		pDXGIAdapter->Release();
		pDXGIAdapter = nullptr;

		pIDXGIFactory->Release();
		pIDXGIFactory = nullptr;

		return result;
	}

	void RgGraphicsContextDX11::releaseSwapChain()
	{
		m_pSwapChain->Release();
		m_pSwapChain = nullptr;
	}

	HRESULT RgGraphicsContextDX11::createRenderTarget()
	{
		HRESULT hr;

		//DEPTH STENCIL BUFFER
		D3D11_TEXTURE2D_DESC depthBufferDesc;
		ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
		depthBufferDesc.Width = m_settings.BufferWidth;
		depthBufferDesc.Height = m_settings.BufferHeight;
		depthBufferDesc.MipLevels = 1;
		depthBufferDesc.ArraySize = 1;
		depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthBufferDesc.SampleDesc.Count = 1;
		depthBufferDesc.SampleDesc.Quality = 0;
		depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthBufferDesc.CPUAccessFlags = 0;
		depthBufferDesc.MiscFlags = 0;

		hr = m_pD3D11Device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer);
		HR_CEHCK(hr);

		//DEPTH STENCIL STATE
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

		depthStencilDesc.StencilEnable = true;
		depthStencilDesc.StencilReadMask = 0xFF;
		depthStencilDesc.StencilWriteMask = 0xFF;

		depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		hr = m_pD3D11Device->CreateDepthStencilState(&depthStencilDesc, &m_pdepthStencilState);
		HR_CEHCK(hr);

		m_pD3D11DeviceContext->OMSetDepthStencilState(m_pdepthStencilState, 1);

		//DEPTH STENCIL VIEW
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
		depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0;

		hr = m_pD3D11Device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_pdepthStencilView);
		HR_CEHCK(hr);

		//RTV
		DXGI_SWAP_CHAIN_DESC swapchainDesc;
		m_pSwapChain->GetDesc(&swapchainDesc);

		ID3D11Texture2D *pBackBuffer;
		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
		ZeroMemory(&rtvDesc, sizeof(rtvDesc));
		rtvDesc.Format = swapchainDesc.BufferDesc.Format;
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

		hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		hr = m_pD3D11Device->CreateRenderTargetView(pBackBuffer, &rtvDesc, &m_pRenderTargetView);
		HR_CEHCK(hr);

		m_pD3D11DeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pdepthStencilView);

		pBackBuffer->Release();

		D3D11_RASTERIZER_DESC rasterDesc;
		rasterDesc.AntialiasedLineEnable = false;
		rasterDesc.CullMode = D3D11_CULL_NONE;
		rasterDesc.DepthBias = 0;
		rasterDesc.DepthBiasClamp = 0.0f;
		rasterDesc.DepthClipEnable = true;
		rasterDesc.FillMode = D3D11_FILL_SOLID;;
		rasterDesc.FrontCounterClockwise = false;
		rasterDesc.MultisampleEnable = false;
		rasterDesc.ScissorEnable = false;
		rasterDesc.SlopeScaledDepthBias = 0.0f;

		hr = m_pD3D11Device->CreateRasterizerState(&rasterDesc, &m_pRasterizerState);

		m_pD3D11DeviceContext->RSSetState(m_pRasterizerState);

		//VIEW PORT
		D3D11_VIEWPORT viewport;
		viewport.Width = (float)m_settings.BufferWidth;
		viewport.Height = (float)m_settings.BufferHeight;
		viewport.MaxDepth = 1.0f;
		viewport.MinDepth = 0.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		m_pD3D11DeviceContext->RSSetViewports(1, &viewport);

		RgLogD() << "create render target done!";
		return S_OK;
	}
	HRESULT RgGraphicsContextDX11::clearRenderTarget()
	{
		if (m_pRenderTargetView) {
			m_pRenderTargetView->Release();
			m_pRenderTargetView = nullptr;
		}

		if (m_depthStencilBuffer) {
			m_depthStencilBuffer->Release();
			m_depthStencilBuffer = nullptr;
		}

		if (m_pdepthStencilState) {
			m_pdepthStencilState->Release();
			m_pdepthStencilState = nullptr;
		}
		if (m_pdepthStencilView) {
			m_pdepthStencilView->Release();
			m_pdepthStencilView = nullptr;
		}
		if (m_pRasterizerState)
		{
			m_pRasterizerState->Release();
			m_pRasterizerState = nullptr;
		}
		return S_OK;
	}
	void RgGraphicsContextDX11::DrawSetPrimitiveTopology()
	{
	}
	void RgGraphicsContextDX11::DrawIndexed(unsigned int size)
	{
		m_pD3D11DeviceContext->DrawIndexed(size, 0, 0);
	}
	std::shared_ptr<RgShader> RgGraphicsContextDX11::CompileShaderFromFile(std::wstring filepath, RgShaderOptions & options)
	{

		ID3DBlob * shaderBlob = nullptr;
		HRESULT result = D3DCompileFromFile(filepath.c_str(), nullptr, nullptr, "main", "vs_4_0_level_9_1", D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY, 0, &shaderBlob, nullptr);
		HR_CEHCK(result);
		if (shaderBlob == nullptr) {
			return nullptr;
		}
		
		ID3D11VertexShader * shader = nullptr;
		result = m_pD3D11Device->CreateVertexShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &shader);
		if (result != S_OK) {
			RgLogE() << "create shader error";
			shaderBlob->Release();
			shaderBlob = nullptr;
			return nullptr;
		}

		return std::make_shared<RgShaderDX11>(options,shader);

	}
	RgBuffer* RgGraphicsContextDX11::CreateBuffer(RgBufferSettings settings)
	{
		auto buffer = new RgBufferDX11(settings);
		HRESULT hr = buffer->Create(m_pD3D11Device);
		HR_CEHCK(hr);

		if (buffer != nullptr) {
			m_vBuffers.push_back(buffer);
		}
		return buffer;
	}
	void ConvertInputLayout(D3D11_INPUT_ELEMENT_DESC& desc,const RgInputLayoutElement element) {
		desc.SemanticName = element.SemanticName;
		desc.SemanticIndex = element.SemanticIndex;
		desc.Format = DXGI_FORMAT_R32G32_FLOAT;
		desc.InputSlot = element.InputSlot;
		desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		desc.AlignedByteOffset = 0;
		desc.InstanceDataStepRate = 0;
	}

	RgInputLayout * RgGraphicsContextDX11::CreateInputLayout(const RgInputLayoutElement * elements, const unsigned int size)
	{
		auto layout = new RgInputLayout(elements, size);
		D3D11_INPUT_ELEMENT_DESC * desc = new D3D11_INPUT_ELEMENT_DESC[size];
		for (unsigned int i = 0; i < size; i++)
		{
			ConvertInputLayout(desc[i],elements[i]);
		}
		//m_pD3D11Device->CreateInputLayout(desc,size,)

		return layout;
	}
	void RgGraphicsContextDX11::resizeBuffer(unsigned int width, unsigned int height)
	{

		if (m_pD3D11Device == nullptr) return;

		clearRenderTarget();

		RgLogD() << "resize buffer";
		HRESULT hr = m_pSwapChain->ResizeBuffers(2, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
		HR_CEHCK(hr);

		m_settings.BufferWidth = width;
		m_settings.BufferHeight = height;

		createRenderTarget();
	}

	float color[4] = { 0.1f,0.4f,0.3f,1.0f };

	void RgGraphicsContextDX11::render()
	{

		m_pD3D11DeviceContext->ClearRenderTargetView(m_pRenderTargetView, color);
		m_pD3D11DeviceContext->ClearDepthStencilView(m_pdepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

		m_pSwapChain->Present(0, 0);
	}
}

