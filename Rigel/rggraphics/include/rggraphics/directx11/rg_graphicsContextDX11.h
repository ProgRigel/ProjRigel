#pragma once
#include "rggraphics_inc.h"
#include "rg_graphicscontext.h"
#include "rg_rasterizer_state.h"
#include "rg_depthstencil_state.h"
#include "rg_blend_state.h"
#include "rg_graphicsAPI.h"

#include <d3d11.h>
#include <dxgi.h>
#include <map>


namespace rg {

	class RgTextureDX11;

	class RgGraphicsContextDX11 : public RgGraphicsContext
	{
	protected:
		RgGraphicsContextDX11();
		~RgGraphicsContextDX11();

		void init(RG_GRAPHICS_INIT_SETTINGS *settings);
		void release();

		void DrawSetBuffer(std::shared_ptr<RgBuffer> buffer);
		void DrawSetMaterial(std::shared_ptr<RgMaterial> material);
		void DrawSetShader(std::shared_ptr<RgShader> shader);
		void DrawSetPrimitiveTopology();
		void DrawIndexed(unsigned int size);

	public:
		std::shared_ptr<RgShader> CompileShaderFromFile(std::wstring filepath, RgShaderOptions& options);
		RgBuffer* CreateBuffer(RgBufferSettings settings);
		std::shared_ptr<RgTexture> CreateTexture(RgTextureSettings& settings);
		RgInputLayout * CreateInputLayout(const RgInputLayoutElement * elements, const unsigned int size, std::shared_ptr<RgShader> vertexShader);
		RgRenderContext * CreateDeferredContext();
		RgRasterizerState * CreateRasterizerState(const RgRasterizerSettings);
		RgDepthStencilState* CreateDepthStencilState(const RgDepthStencilSettings&);
		RgBlendState * CreateBlendState(const RgBlendStateSettings&);
		RgGraphicsSampler* CreateSampler(const RgGraphicsSamplerSettings&);

		void GetDisplayModeList();

		void SetFullScreen(bool fullscreen);

		void resizeBuffer(unsigned int width, unsigned int height);
		void render();
		void prerender();

	protected:
		ID3D11ShaderResourceView * CreateShaderResourceView(RgTextureDX11* texture);
	public:

		const RgViewPort* GetViewPortDefault();

	private:
		ID3D11Device *m_pD3D11Device = nullptr;
		ID3D11DeviceContext *m_pD3D11DeviceContext = nullptr;
		IDXGISwapChain * m_pSwapChain = nullptr;

		ID3D11Texture2D * m_depthStencilBuffer = nullptr;
		RgDepthStencilState * m_pDepthStencilState = nullptr;

		D3D11_VIEWPORT m_sViewPort;

		HRESULT createDeviceAndContext();
		void releaseDeviceAndContext();
		HRESULT createSwapChain();
		void releaseSwapChain();

		HRESULT createRenderTarget();
		HRESULT clearRenderTarget();

	private:
		std::vector<ID3D11InputLayout*> m_vInputLayouts;
		ID3D11SamplerState * m_pSamplerState = nullptr;

	public:
		friend class RgGraphicsAPI;
	};


#pragma region Convert
	namespace directx {
		DXGI_FORMAT MapFormat(RgGraphicsFormat fmt);
		unsigned int MapBind(RgGraphicsBindFlag bind);
		D3D11_USAGE MapUsage(RgGraphicsUsage usage);
		D3D11_FILTER MapFilter(RgGraphicsFilter filter);
		D3D11_TEXTURE_ADDRESS_MODE MapTextureAddressMode(RgGraphicsTextureAddressMode addressmode);

		D3D11_RENDER_TARGET_BLEND_DESC MpaRenderTargetBlend(RgRenderTargetBlendSetting rts);
		D3D11_BLEND_OP MapBlendOp(RgBlendOp op);
		D3D11_BLEND MapBlend(RgBlend blend);

		void ConvertDepthStencilState(const RgDepthStencilSettings& settings, D3D11_DEPTH_STENCIL_DESC& desc);
		void ConvertRasterizerState(const RgRasterizerSettings& settings, D3D11_RASTERIZER_DESC& desc);
		void ConvertBlendState(const RgBlendStateSettings& settings, D3D11_BLEND_DESC& desc);
		void ConvertRenderTargetBlendState(const RgRenderTargetBlendSetting& settings, D3D11_RENDER_TARGET_BLEND_DESC&desc);

		void ConvertTexture(const RgTextureSettings& settings, D3D11_TEXTURE2D_DESC& desc);
		void ConvertSampler(const RgGraphicsSamplerSettings& settings, D3D11_SAMPLER_DESC& desc);
	}
#pragma endregion

}