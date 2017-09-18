#include "rggraphics.h"
#include "rg_graphicsContextDX11.h"
#include "rg_shaderDX11.h"
#include "rg_bufferDX11.h"
#include "rg_render_context_dx11.h"
#include "rg_inputlayout.h"
#include "rg_buffer.h"
#include "rg_rasterizer_state.h"
#include "rg_rasterizer_state_dx11.h"
#include "rg_depthstencil_state_dx11.h"
#include "rg_render_target.h"

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
		auto renderctx = new RgRenderContextDX11(true);
		renderctx->m_pDeviceContext = m_pD3D11DeviceContext;
		m_pRenderContext = renderctx;
	}

	void RgGraphicsContextDX11::release()
	{
		std::cout << "release dx11 api" << std::endl;

		for each(auto inputlayout in m_vInputLayouts) {
			if (inputlayout != nullptr) {
				inputlayout->Release();
				inputlayout = nullptr;
			}
		}

		for (auto rs : m_vRasterState) {
			if (rs != nullptr) {
				rs->Release();
				rs = nullptr;
			}
		}

		for (auto dss : m_vDepthStencilState) {
			if (dss != nullptr) {
				dss->Release();
				dss = nullptr;
			}
		}

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
		//test::cnm
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


		//DEPTH STENCIL VIEW
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
		depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0;

		ID3D11DepthStencilView *m_pdepthStencilView;
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
		ID3D11RenderTargetView *m_pRenderTargetView;
		hr = m_pD3D11Device->CreateRenderTargetView(pBackBuffer, &rtvDesc, &m_pRenderTargetView);
		HR_CEHCK(hr);

		m_pD3D11DeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pdepthStencilView);

		pBackBuffer->Release();

		m_pRenderTarget = new RgRenderTarget();
		m_pRenderTarget->SetColorBufferPtr(m_pRenderTargetView);
		m_pRenderTarget->SetDepthBufferPtr(m_pdepthStencilView);
		m_pRenderTarget->BufferWidth = m_settings.BufferWidth;
		m_pRenderTarget->BufferHeight = m_settings.BufferHeight;

		//VIEW PORT
		D3D11_VIEWPORT viewport;
		viewport.Width = (float)m_settings.BufferWidth;
		viewport.Height = (float)m_settings.BufferHeight;

		viewport.MaxDepth = 1.0f;
		viewport.MinDepth = 0.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		m_sViewPort = viewport;
		

		return S_OK;
	}
	HRESULT RgGraphicsContextDX11::clearRenderTarget()
	{
		if (m_pRenderTarget != nullptr) {
			ID3D11RenderTargetView * rtv = (ID3D11RenderTargetView*)m_pRenderTarget->GetColorBufferPtr();
			if (rtv != nullptr) {
				rtv->Release();
				m_pRenderTarget->SetColorBufferPtr(nullptr);
			}
			ID3D11DepthStencilView * dsv = (ID3D11DepthStencilView*)m_pRenderTarget->GetDepthBufferPtr();
			if (dsv != nullptr) {
				dsv->Release();
				m_pRenderTarget->SetDepthBufferPtr(nullptr);
			}
			delete m_pRenderTarget;
			m_pRenderTarget = nullptr;
		}


		if (m_depthStencilBuffer) {
			m_depthStencilBuffer->Release();
			m_depthStencilBuffer = nullptr;
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
		auto cached = this->GetCachedShader(filepath);
		if (cached) {
			return std::shared_ptr<RgShader>(cached);
		}

		const char* entrypoint = options.EntryPoint.c_str();
		const char* shadertarget = options.ShaderTarget.c_str();

		ID3DBlob * shaderBlob = nullptr;
		HRESULT result = D3DCompileFromFile(filepath.c_str(), nullptr, nullptr, entrypoint, shadertarget, D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY, 0, &shaderBlob, nullptr);
		HR_CEHCK(result);
		if (result != S_OK) {
			RgLogE() << "compile shader error "<< options.ShaderTarget;
			if (shaderBlob) {
				shaderBlob->Release();
				shaderBlob = nullptr;
			}
			return nullptr;
		}

		std::shared_ptr<RgShader> ret = nullptr;
		
		if (options.ShaderEntry == RG_SHADER_ENTRY::Vertex) {
			ID3D11VertexShader * shader = nullptr;
			result = m_pD3D11Device->CreateVertexShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &shader);
			HR_CEHCK(result);
			if (result != S_OK) {
				RgLogE() << "create vertex shader error";
				shaderBlob->Release();
				shaderBlob = nullptr;
				return nullptr;
			}
			auto rgshader = std::make_shared<RgShaderDX11>(options, shaderBlob);
			rgshader->m_pVertexShader = shader;
			ret = std::dynamic_pointer_cast<RgShader>(rgshader);
		}
		else if (options.ShaderEntry == RG_SHADER_ENTRY::Pixel) {
			ID3D11PixelShader * shader = nullptr;
			result = m_pD3D11Device->CreatePixelShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &shader);
			HR_CEHCK(result);
			if (result != S_OK) {
				RgLogE() << "create pixel shader error";
				shaderBlob->Release();
				shaderBlob = nullptr;
				return nullptr;
			}
			auto rgshader = std::make_shared<RgShaderDX11>(options, shaderBlob);
			rgshader->m_pPixelShader = shader;

			ret = std::dynamic_pointer_cast<RgShader>(rgshader);
		}
		
		m_mShaderCaches.insert(std::make_pair(filepath, std::shared_ptr<RgShader>(ret)));

		return ret;
	}
	RgBuffer* RgGraphicsContextDX11::CreateBuffer(RgBufferSettings settings)
	{
		auto buffer = new RgBufferDX11(settings);
		buffer->m_setting = settings;
		HRESULT hr = buffer->Create(m_pD3D11Device);
		HR_CEHCK(hr);

		if (buffer != nullptr) {
			m_vBuffers.push_back(buffer);
			return buffer;
		}
		else
		{
			delete buffer;
			return nullptr;
		}
		
	}
	std::shared_ptr<RgTexture> RgGraphicsContextDX11::CreateTexture(RgTextureSettings & settings)
	{
		return std::shared_ptr<RgTexture>();
	}
	void ConvertInputLayout(D3D11_INPUT_ELEMENT_DESC& desc,const RgInputLayoutElement element) {
		desc.SemanticName = element.SemanticName;
		desc.SemanticIndex = element.SemanticIndex;
		if(element.Format == RgGraphicsFormat::R32G32_FLOAT)
			desc.Format = DXGI_FORMAT_R32G32_FLOAT;
		else if (element.Format == RgGraphicsFormat::R32G32B32_FLOAT)
		{
			desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		}
		desc.InputSlot = element.InputSlot;
		desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		desc.AlignedByteOffset = element.AlignedByteOffset;
		desc.InstanceDataStepRate = 0;
	}

	RgInputLayout * RgGraphicsContextDX11::CreateInputLayout(const RgInputLayoutElement * elements, const unsigned int size,std::shared_ptr<RgShader> vertexShader)
	{
		auto layout = new RgInputLayout(elements, size);
		D3D11_INPUT_ELEMENT_DESC * desc = new D3D11_INPUT_ELEMENT_DESC[size];
		for (unsigned int i = 0; i < size; i++)
		{
			ConvertInputLayout(desc[i],elements[i]);
		}
		RgShader * shaderptr = vertexShader.get();
		auto shaderblob = dynamic_cast<RgShaderDX11*>(shaderptr)->m_pShaderBlob;


		ID3D11InputLayout *inputlayout = nullptr;
		HRESULT hr = m_pD3D11Device->CreateInputLayout(desc, size, shaderblob->GetBufferPointer(), shaderblob->GetBufferSize(), &inputlayout);
		HR_CEHCK(hr);
		if (hr != S_OK) {
			RgLogE() << "create inputlayout error";
			delete layout;
			return nullptr;
		}

		layout->pLayout = inputlayout;

		m_vInputLayouts.push_back(inputlayout);

		return layout;
	}
	RgRenderContext * RgGraphicsContextDX11::CreateDeferredContext()
	{
		ID3D11DeviceContext * devicectx = nullptr;
		HRESULT hr = m_pD3D11Device->CreateDeferredContext(0, &devicectx);
		HR_CEHCK(hr);
		if (hr != S_OK) {
			return nullptr;
		}
		RgRenderContextDX11 * ctx = new RgRenderContextDX11(false);
		ctx->m_pDeviceContext = devicectx;
		m_vRenderContexts.push_back(ctx);
		return ctx;
	}
	RgRasterizerState * RgGraphicsContextDX11::CreateRasterizerState(const RgRasterizerSettings settings)
	{
		auto rs = new RgRasterizerStateDX11(settings);
		D3D11_RASTERIZER_DESC desc;
		ConvertRasterizerState(settings, desc);
		ID3D11RasterizerState * dxrs = nullptr;
		HRESULT hr = m_pD3D11Device->CreateRasterizerState(&desc, &dxrs);
		HR_CEHCK(hr);
		rs->m_ptr = dxrs;
		return rs;
	}
	RgDepthStencilState * RgGraphicsContextDX11::CreateDepthStencilState(const RgDepthStencilSettings & settings)
	{
		auto dss = new RgDepthStencilStateDX11(settings);
		D3D11_DEPTH_STENCIL_DESC desc;
		ConvertDepthStencilState(settings, desc);
		ID3D11DepthStencilState * dxdss = nullptr;
		HRESULT hr = m_pD3D11Device->CreateDepthStencilState(&desc, &dxdss);
		HR_CEHCK(hr);
		dss->m_state = dxdss;

		m_vDepthStencilState.push_back(dss);
		return dss;
	}
	void RgGraphicsContextDX11::resizeBuffer(unsigned int width, unsigned int height)
	{

		if (m_pD3D11Device == nullptr) return;

		EventBeforeResize.emit();

		clearRenderTarget();
		HRESULT hr = m_pSwapChain->ResizeBuffers(2, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
		HR_CEHCK(hr);

		m_settings.BufferWidth = width;
		m_settings.BufferHeight = height;


		createRenderTarget();
		m_pRenderTarget->BufferWidth = width;
		m_pRenderTarget->BufferHeight = height;

		EventAfterResize.emit(width,height);
	}

	float color[4] = { 0.1f,0.4f,0.3f,1.0f };

	void RgGraphicsContextDX11::render()
	{
		m_pSwapChain->Present(0, 0);
	}
	void RgGraphicsContextDX11::prerender()
	{

	}
	const RgViewPort * RgGraphicsContextDX11::GetViewPortDefault()
	{
		return (RgViewPort*)&m_sViewPort;
	}
}

