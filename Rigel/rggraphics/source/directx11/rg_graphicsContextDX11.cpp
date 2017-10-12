#include "rggraphics.h"
#include "rg_inputlayout.h"
#include "rg_buffer.h"
#include "rg_rasterizer_state.h"
#include "rg_render_target.h"
#include "rg_graphics_display_mode.h"

#include "directx11\rg_texture_dx11.h"
#include "directx11\rg_sampler_dx11.h"
#include "directx11\rg_blend_state_dx11.h"
#include "directx11\rg_rasterizer_state_dx11.h"
#include "directx11\rg_depthstencil_state_dx11.h"
#include "directx11\rg_graphicsContextDX11.h"
#include "directx11\rg_shaderDX11.h"
#include "directx11\rg_bufferDX11.h"
#include "directx11\rg_render_context_dx11.h"

#define HR_CEHCK(hr) if(hr != S_OK){RgLogE()<<rg::HR_CODE(hr) << rg::HrToMessage(hr);}
#define RELEASE_COM(h) if(h!= nullptr) h->Release(); h = nullptr;

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
		GetDisplayModeList();
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

		if (m_depthStencilBuffer != nullptr) {
			m_depthStencilBuffer->Release();
			m_depthStencilBuffer = nullptr;
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
		unsigned int creationFlag = 0;
#ifdef  _DEBUG
		creationFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif // DEBUG || _DEBUG


		D3D_FEATURE_LEVEL featureLevel;
		CONST D3D_FEATURE_LEVEL featureLevelArray[1] = {
			D3D_FEATURE_LEVEL_11_0 };
		HRESULT result = D3D11CreateDevice(
			NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			creationFlag,
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

		pBackBuffer->Release();

		D3D11_TEXTURE2D_DESC bufferdesc;
		pBackBuffer->GetDesc(&bufferdesc);

		auto width = bufferdesc.Width;
		auto height = bufferdesc.Height;

		//DEPTH STENCIL BUFFER
		D3D11_TEXTURE2D_DESC depthBufferDesc;
		ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

		RgTextureSettings settings;
		settings.Width = width;
		settings.Height = height;
		settings.MipLevels = 1;
		settings.ArraySize = 1;
		settings.Format = RgGraphicsFormat::D24_UNORM_S8_UINT;
		settings.BindFlags = RgGraphicsBindFlag::DepthStencil;
		settings.Usage = RgGraphicsUsage::DEFAULT;
		settings.DX_CPUAccessFlag = 0;
		settings.DX_MiscFlags = 0;
		settings.SampleDesc.Count = 1;
		settings.SampleDesc.Quality = 0;

		directx::ConvertTexture(settings, depthBufferDesc);

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

		

		m_pD3D11DeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pdepthStencilView);

		

		m_pRenderTarget = new RgRenderTarget();
		m_pRenderTarget->SetColorBufferPtr(m_pRenderTargetView);
		m_pRenderTarget->SetDepthBufferPtr(m_pdepthStencilView);
		m_pRenderTarget->BufferWidth = width;
		m_pRenderTarget->BufferHeight = height;

		//VIEW PORT
		D3D11_VIEWPORT viewport;
		viewport.Width = (float)width;
		viewport.Height = (float)height;

		viewport.MaxDepth = 1.0f;
		viewport.MinDepth = 0.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		m_sViewPort = viewport;

		m_settings.BufferWidth = width;
		m_settings.BufferHeight = height;
		

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
		D3D11_TEXTURE2D_DESC desc;
		directx::ConvertTexture(settings, desc);

		ID3D11Texture2D* dxtexture = nullptr;
		HRESULT hr = m_pD3D11Device->CreateTexture2D(&desc, nullptr, &dxtexture);
		HR_CEHCK(hr);
		if (hr != S_OK || dxtexture == nullptr) return nullptr;

		auto rgtex = std::make_shared<RgTextureDX11>(settings);
		rgtex->m_pd3d11tex2d = dxtexture;
		auto ret = std::dynamic_pointer_cast<RgTexture>(rgtex);

		m_vTexture.push_back(ret);

		CreateShaderResourceView(rgtex.get());

		return ret;
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
		else if (element.Format == RgGraphicsFormat::R32G32B32A32_FLOAT) {
			desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
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
		directx::ConvertRasterizerState(settings, desc);
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
		directx::ConvertDepthStencilState(settings, desc);
		ID3D11DepthStencilState * dxdss = nullptr;
		HRESULT hr = m_pD3D11Device->CreateDepthStencilState(&desc, &dxdss);
		HR_CEHCK(hr);
		if (hr != S_OK) {
			RgLogE() << "create depth stencil state dx error:" << HrToError(hr);
		}
		RG_ASSERT(dxdss);
		dss->m_state = dxdss;

		m_vDepthStencilState.push_back(dss);
		return dss;
	}
	RgBlendState * RgGraphicsContextDX11::CreateBlendState(const RgBlendStateSettings & settings)
	{
		auto blendstate = new RgBlendStateDX11(settings);
		D3D11_BLEND_DESC desc;
		directx::ConvertBlendState(settings, desc);

		ID3D11BlendState * dxblendstate = nullptr;
		HRESULT hr = m_pD3D11Device->CreateBlendState(&desc, &dxblendstate);
		HR_CEHCK(hr);
		if (hr != S_OK) {
			RgLogE() << "create blend state dx error:" << HR_CODE(hr);
		}
		RG_ASSERT(dxblendstate);
		blendstate->m_ptr = dxblendstate;

		m_vBlendState.push_back(blendstate);
		return blendstate;
	}
	RgGraphicsSampler * RgGraphicsContextDX11::CreateSampler(const RgGraphicsSamplerSettings &)
	{
		RgGraphicsSamplerSettings settings;

		D3D11_SAMPLER_DESC samplerDesc;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.MipLODBias = 0.0F;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samplerDesc.BorderColor[0] = 0;
		samplerDesc.BorderColor[1] = 0;
		samplerDesc.BorderColor[2] = 0;
		samplerDesc.BorderColor[3] = 0;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = 0;

		ID3D11SamplerState * sampler = nullptr;
		HRESULT hr = m_pD3D11Device->CreateSamplerState(&samplerDesc, &sampler);
		HR_CEHCK(hr);
		if (hr != S_OK || sampler == nullptr) {
			RgLogE() << "create sampler state error";
			return nullptr;
		}

		RgGraphicsSamplerDX11 * rgsampler = new RgGraphicsSamplerDX11(settings);
		rgsampler->m_psampler = sampler;


		m_vSampler.push_back(rgsampler);

		return rgsampler;
	}
	void RgGraphicsContextDX11::GetDisplayModeList()
	{
		if (m_pD3D11Device == nullptr) return;

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

		IDXGIOutput * adapterOutput;
		unsigned int numModes = 0;
		pDXGIAdapter->EnumOutputs(0, &adapterOutput);
		result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr);
		if (result != S_OK) {
			RgLogE() << HrToMessage(result);
		}

		if (numModes == 0) return;

		DXGI_MODE_DESC * modelist = new DXGI_MODE_DESC[numModes];
		
		result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, modelist);
		if (result != S_OK) {
			RgLogE() << HrToMessage(result);
		}

		for (unsigned int i = 0; i < numModes; i++) {
			RgGraphicsDisplayMode displaymode;
			displaymode.Width = modelist[i].Width;
			displaymode.Height = modelist[i].Height;
			displaymode.RefreshRateDenominator = modelist[i].RefreshRate.Denominator;
			displaymode.RefreshRateNumerator = modelist[i].RefreshRate.Numerator;

			m_vDisplayModes.push_back(displaymode);
		}

		//get monitor info
		DXGI_OUTPUT_DESC outputdesc;
		adapterOutput->GetDesc(&outputdesc);
		HMONITOR hmonitor = outputdesc.Monitor;
		MONITORINFOEX monitorInfo;
		monitorInfo.cbSize = sizeof(MONITORINFOEX);
		GetMonitorInfo(hmonitor, &monitorInfo);
		DEVMODE devMode;
		devMode.dmSize = sizeof(DEVMODE);
		devMode.dmDriverExtra = 0;
		EnumDisplaySettings(monitorInfo.szDevice, ENUM_CURRENT_SETTINGS, &devMode);

		DXGI_MODE_DESC closestMatchMode;
		DXGI_MODE_DESC mode;
		mode.Width = devMode.dmPelsWidth;
		mode.Height = devMode.dmPelsHeight;
		mode.RefreshRate.Denominator = 0;
		mode.RefreshRate.Numerator = 0;
		mode.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		mode.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		mode.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		result = adapterOutput->FindClosestMatchingMode(&mode, &closestMatchMode,nullptr);
		if (result != S_OK) {
			RgLogE() << HrToMessage(result);
		}

		m_DisplayModeDefault.Width = closestMatchMode.Width;
		m_DisplayModeDefault.Height = closestMatchMode.Height;
		m_DisplayModeDefault.RefreshRateDenominator = closestMatchMode.RefreshRate.Denominator;
		m_DisplayModeDefault.RefreshRateNumerator = closestMatchMode.RefreshRate.Numerator;

		delete[] modelist;

		RELEASE_COM(pDXGIDevice);
		RELEASE_COM(pDXGIAdapter);
		RELEASE_COM(adapterOutput);
	}
	void RgGraphicsContextDX11::SetFullScreen(bool fullscreen)
	{
		HRESULT result = m_pSwapChain->SetFullscreenState(fullscreen, nullptr);
		if (result != S_OK) {
			RgLogE() << "dx11 setfullscreen error:" << HrToMessage(result);
		}
		
	}
	void RgGraphicsContextDX11::resizeBuffer(unsigned int width, unsigned int height)
	{
		if (m_pD3D11Device == nullptr) return;

		EventBeforeResize.emit();


		clearRenderTarget();
		//Automatically choose the width and height to match the client rect for HWNDs.
		HRESULT hr = m_pSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
		HR_CEHCK(hr);

		createRenderTarget();

		EventAfterResize.emit(m_settings.BufferWidth, m_settings.BufferHeight);
	}

	float color[4] = { 0.1f,0.4f,0.3f,1.0f };

	void RgGraphicsContextDX11::render()
	{
		m_pSwapChain->Present(0, 0);
	}
	void RgGraphicsContextDX11::prerender()
	{

	}
	ID3D11ShaderResourceView * RgGraphicsContextDX11::CreateShaderResourceView(RgTextureDX11 * texture)
	{
		if (texture == nullptr) return nullptr;
		if (texture->m_psrv != nullptr) {
			RgLogW() << "srv not null";
			return texture->m_psrv;
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC desc;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Format = directx::MapFormat(texture->m_sSettings.Format);
		desc.Texture2D.MipLevels = -1;
		desc.Texture2D.MostDetailedMip = 0;

		ID3D11ShaderResourceView * srv = nullptr;

		HRESULT hr = m_pD3D11Device->CreateShaderResourceView(texture->m_pd3d11tex2d, &desc, &srv);
		HR_CEHCK(hr);
		if (srv == nullptr) {
			RgLogE() << "create shader resources view error";
			return nullptr;
		}

		texture->m_psrv = srv;
		return texture->m_psrv;
	}
	const RgViewPort * RgGraphicsContextDX11::GetViewPortDefault()
	{
		return (RgViewPort*)&m_sViewPort;
	}
}

#pragma region map

DXGI_FORMAT rg::directx::MapFormat(RgGraphicsFormat fmt)
{
	static std::unordered_map<RgGraphicsFormat, DXGI_FORMAT> map = {
		{ RgGraphicsFormat::UNKNOWN,				DXGI_FORMAT::DXGI_FORMAT_UNKNOWN },
		{ RgGraphicsFormat::R32G32_FLOAT,			DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT },
		{ RgGraphicsFormat::R32G32B32_FLOAT,		DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT },
		{ RgGraphicsFormat::R32G32B32A32_FLOAT,		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT },
		{ RgGraphicsFormat::R8G8B8A8_UNORM,			DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM },
		{ RgGraphicsFormat::R8G8B8A8_UINT,			DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UINT},
		{ RgGraphicsFormat::D24_UNORM_S8_UINT,		DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT},
	};
	return map[fmt];
}
unsigned int rg::directx::MapBind(RgGraphicsBindFlag bind)
{
	static std::unordered_map<RgGraphicsBindFlag, unsigned int> map = {
		{ RgGraphicsBindFlag::ShaderResource,		D3D11_BIND_SHADER_RESOURCE },
		{ RgGraphicsBindFlag::DepthStencil,			D3D11_BIND_DEPTH_STENCIL},
		{ RgGraphicsBindFlag::VertexBuffer,			D3D11_BIND_VERTEX_BUFFER },
		{ RgGraphicsBindFlag::ConstantBuffer,		D3D11_BIND_CONSTANT_BUFFER },
		{ RgGraphicsBindFlag::IndexBuffer,			D3D11_BIND_INDEX_BUFFER },
		{ RgGraphicsBindFlag::StreamOutput,			D3D11_BIND_STREAM_OUTPUT },
		{ RgGraphicsBindFlag::RenderTarget,			D3D11_BIND_RENDER_TARGET },
		{ RgGraphicsBindFlag::UnorderedAccess,		D3D11_BIND_UNORDERED_ACCESS },
		{ RgGraphicsBindFlag::Decoder,				D3D11_BIND_DECODER },
		{ RgGraphicsBindFlag::VideoEncoder,			D3D11_BIND_VIDEO_ENCODER },
	};

	return map[bind];
}
D3D11_USAGE rg::directx::MapUsage(RgGraphicsUsage usage)
{
	static std::unordered_map<RgGraphicsUsage, D3D11_USAGE> map = {
		{ RgGraphicsUsage::DEFAULT,D3D11_USAGE::D3D11_USAGE_DEFAULT },
		{ RgGraphicsUsage::DYNAMIC,D3D11_USAGE::D3D11_USAGE_DYNAMIC },
		{ RgGraphicsUsage::STAGE,D3D11_USAGE::D3D11_USAGE_STAGING },
		{ RgGraphicsUsage::IMMUTABLE,D3D11_USAGE::D3D11_USAGE_IMMUTABLE },
	};
	return map[usage];
}
D3D11_FILTER rg::directx::MapFilter(RgGraphicsFilter filter)
{
	static std::unordered_map<RgGraphicsFilter, D3D11_FILTER> map = {
		{RgGraphicsFilter::MinMagPointMipLinear,D3D11_FILTER_MIN_MAG_MIP_LINEAR},
		{ RgGraphicsFilter::MinMagMipPoint,D3D11_FILTER_MIN_MAG_MIP_POINT },
		{ RgGraphicsFilter::Anisotropic,D3D11_FILTER_ANISOTROPIC}
	};

	return map[filter];
}
D3D11_TEXTURE_ADDRESS_MODE rg::directx::MapTextureAddressMode(RgGraphicsTextureAddressMode addressmode)
{
	static std::unordered_map<RgGraphicsTextureAddressMode, D3D11_TEXTURE_ADDRESS_MODE> map = {
		{ RgGraphicsTextureAddressMode::Wrap,D3D11_TEXTURE_ADDRESS_WRAP},
		{ RgGraphicsTextureAddressMode::Mirror,D3D11_TEXTURE_ADDRESS_MIRROR},
		{ RgGraphicsTextureAddressMode::Clamp,D3D11_TEXTURE_ADDRESS_CLAMP},
		{ RgGraphicsTextureAddressMode::Border,D3D11_TEXTURE_ADDRESS_BORDER},
		{ RgGraphicsTextureAddressMode::MirrorOnce,D3D11_TEXTURE_ADDRESS_MIRROR_ONCE}
	};

	return map[addressmode];
}
D3D11_RENDER_TARGET_BLEND_DESC rg::directx::MpaRenderTargetBlend(RgRenderTargetBlendSetting rts)
{
	return D3D11_RENDER_TARGET_BLEND_DESC();
}
D3D11_BLEND_OP rg::directx::MapBlendOp(RgBlendOp op)
{
	static std::unordered_map<RgBlendOp, D3D11_BLEND_OP> map = {
		{RgBlendOp::Add,			D3D11_BLEND_OP_ADD},
		{RgBlendOp::Subtract,		D3D11_BLEND_OP_SUBTRACT},
		{RgBlendOp::RevSubtract,	D3D11_BLEND_OP_REV_SUBTRACT},
		{RgBlendOp::Max,			D3D11_BLEND_OP_MAX},
		{RgBlendOp::Min,			D3D11_BLEND_OP_MIN}
	};
	return map[op];
}
D3D11_BLEND rg::directx::MapBlend(RgBlend blend)
{
	static std::unordered_map<RgBlend, D3D11_BLEND> map = {
		{ RgBlend::Zero,				D3D11_BLEND_ZERO },
		{ RgBlend::One,					D3D11_BLEND_ONE},
		{ RgBlend::Src1Color,			D3D11_BLEND_SRC_COLOR },
		{ RgBlend::InvSrcColor,			D3D11_BLEND_INV_SRC_COLOR },
		{ RgBlend::SrcAlpha,			D3D11_BLEND_SRC_ALPHA},
		{ RgBlend::InvSrc1Alpha,		D3D11_BLEND_INV_SRC_ALPHA},
		{ RgBlend::DstAlpha,			D3D11_BLEND_DEST_ALPHA },
		{ RgBlend::InvDstAlpha,			D3D11_BLEND_INV_DEST_ALPHA },
		{ RgBlend::DstColor,			D3D11_BLEND_DEST_COLOR },
		{ RgBlend::InvDstColor,			D3D11_BLEND_INV_DEST_COLOR },
		{ RgBlend::SrcAlphaSat,			D3D11_BLEND_SRC_ALPHA_SAT },
		{ RgBlend::BlendFactor,			D3D11_BLEND_BLEND_FACTOR },
		{ RgBlend::InvBlendFactor,		D3D11_BLEND_INV_BLEND_FACTOR},
		{ RgBlend::Src1Color,			D3D11_BLEND_SRC1_COLOR},
		{ RgBlend::InvSrc1Color,		D3D11_BLEND_INV_SRC1_COLOR},
		{ RgBlend::Scr1Alpha,			D3D11_BLEND_SRC1_ALPHA },
		{ RgBlend::InvSrc1Alpha,		D3D11_BLEND_INV_SRC1_ALPHA}
	};
	return map[blend];
}
void rg::directx::ConvertDepthStencilState(const RgDepthStencilSettings & settings, D3D11_DEPTH_STENCIL_DESC & desc)
{
	desc.DepthEnable = settings.DepthEnable;
	desc.DepthWriteMask = (D3D11_DEPTH_WRITE_MASK)settings.DepthWriteMask;
	desc.DepthFunc = (D3D11_COMPARISON_FUNC)settings.DepthFunc;

	desc.StencilEnable = settings.StencilEnable;
	desc.StencilReadMask = settings.StencilReadMask;
	desc.StencilWriteMask = settings.StencilWriteMask;

	desc.FrontFace.StencilFailOp = (D3D11_STENCIL_OP)settings.FrontFace.StencilFailOp;
	desc.FrontFace.StencilDepthFailOp = (D3D11_STENCIL_OP)settings.FrontFace.StencilDepthFailOp;
	desc.FrontFace.StencilPassOp = (D3D11_STENCIL_OP)settings.FrontFace.StencilPassOp;
	desc.FrontFace.StencilFunc = (D3D11_COMPARISON_FUNC)settings.FrontFace.StencilFunc;

	desc.BackFace.StencilFailOp = (D3D11_STENCIL_OP)settings.BackFace.StencilFailOp;
	desc.BackFace.StencilDepthFailOp = (D3D11_STENCIL_OP)settings.BackFace.StencilDepthFailOp;
	desc.BackFace.StencilPassOp = (D3D11_STENCIL_OP)settings.BackFace.StencilPassOp;
	desc.BackFace.StencilFunc = (D3D11_COMPARISON_FUNC)settings.BackFace.StencilFunc;
}
void rg::directx::ConvertRasterizerState(const RgRasterizerSettings & settings, D3D11_RASTERIZER_DESC & desc)
{
	desc.AntialiasedLineEnable = settings.AntialiasedLine;
	desc.CullMode = (D3D11_CULL_MODE)settings.CullMode;
	desc.FillMode = (D3D11_FILL_MODE)settings.FillMode;
	desc.DepthBias = settings.DepthBias;
	desc.DepthBiasClamp = settings.DepthBiasClamp;
	desc.DepthClipEnable = settings.DepthClipEnable;
	desc.MultisampleEnable = settings.MultisampleEnable;
	desc.ScissorEnable = settings.ScissorEnable;
	desc.SlopeScaledDepthBias = settings.SlopeScaledDepthBias;
	desc.FrontCounterClockwise = settings.FrontCounterClockwise;
}
void rg::directx::ConvertBlendState(const RgBlendStateSettings & settings, D3D11_BLEND_DESC & desc)
{
	desc.AlphaToCoverageEnable = settings.DX_AlpahToConverageEnable;
	desc.IndependentBlendEnable = settings.DX_IndependentBlendEnable;
	directx::ConvertRenderTargetBlendState(settings.RenderTarget[0], desc.RenderTarget[0]);
	directx::ConvertRenderTargetBlendState(settings.RenderTarget[1], desc.RenderTarget[1]);
	directx::ConvertRenderTargetBlendState(settings.RenderTarget[2], desc.RenderTarget[2]);
	directx::ConvertRenderTargetBlendState(settings.RenderTarget[3], desc.RenderTarget[3]);
	directx::ConvertRenderTargetBlendState(settings.RenderTarget[4], desc.RenderTarget[4]);
	directx::ConvertRenderTargetBlendState(settings.RenderTarget[5], desc.RenderTarget[5]);
	directx::ConvertRenderTargetBlendState(settings.RenderTarget[6], desc.RenderTarget[6]);
	directx::ConvertRenderTargetBlendState(settings.RenderTarget[7], desc.RenderTarget[7]);
}
void rg::directx::ConvertRenderTargetBlendState(const RgRenderTargetBlendSetting & settings, D3D11_RENDER_TARGET_BLEND_DESC & desc)
{
	desc.BlendEnable = settings.BlendEnable;
	desc.BlendOp = MapBlendOp(settings.BlendOp);
	desc.BlendOpAlpha = MapBlendOp(settings.BlendOpAlpha);
	desc.DestBlend = MapBlend(settings.DstBlend);
	desc.DestBlendAlpha = MapBlend(settings.DstBlendAlpha);
	desc.SrcBlend = MapBlend(settings.SrcBlend);
	desc.SrcBlendAlpha = MapBlend(settings.SrcBlend);
	desc.RenderTargetWriteMask = settings.RenderTargetWriteMask;
}
void rg::directx::ConvertTexture(const RgTextureSettings & settings, D3D11_TEXTURE2D_DESC & desc)
{
	desc.Width = settings.Width;
	desc.Height = settings.Height;
	desc.MipLevels = settings.MipLevels;
	desc.ArraySize = settings.ArraySize;
	desc.Format = directx::MapFormat(settings.Format);
	desc.BindFlags = directx::MapBind(settings.BindFlags);
	desc.SampleDesc.Count = settings.SampleDesc.Count;
	desc.SampleDesc.Quality = settings.SampleDesc.Quality;
	desc.Usage = directx::MapUsage(settings.Usage);

	desc.CPUAccessFlags = settings.DX_CPUAccessFlag;
	desc.MiscFlags = settings.DX_MiscFlags;
}
void rg::directx::ConvertSampler(const RgGraphicsSamplerSettings & settings, D3D11_SAMPLER_DESC & desc)
{
}
#pragma endregion


