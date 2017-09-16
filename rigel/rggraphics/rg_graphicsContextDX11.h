#pragma once
#include "rggraphics_inc.h"
#include "rg_graphicscontext.h"
#include "rg_rasterizer_state.h"
#include "rg_depthstencil_state.h"

#include <d3d11.h>
#include <dxgi.h>


namespace rg {


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

		RgInputLayout * CreateInputLayout(const RgInputLayoutElement * elements,const unsigned int size, std::shared_ptr<RgShader> vertexShader);

		RgRenderContext * CreateDeferredContext();

		RgRasterizerState * CreateRasterizerState(const RgRasterizerSettings);
		RgDepthStencilState* CreateDepthStencilState(const RgDepthStencilSettings&);

		void resizeBuffer(unsigned int width, unsigned int height);
		void render();
		void prerender();

	public:
		ID3D11RenderTargetView * GetRenderTargetView();
		ID3D11DepthStencilView * GetDepthStencilView();

		const RgViewPort* GetViewPortDefault();


	private:
		

		ID3D11Device *m_pD3D11Device = nullptr;
		ID3D11DeviceContext *m_pD3D11DeviceContext = nullptr;
		IDXGISwapChain * m_pSwapChain = nullptr;
		
		ID3D11Texture2D * m_depthStencilBuffer = nullptr;
		RgDepthStencilState * m_pDepthStencilState = nullptr;
		ID3D11DepthStencilView *m_pdepthStencilView = nullptr;
		ID3D11RenderTargetView* m_pRenderTargetView = nullptr;

		D3D11_VIEWPORT m_sViewPort;

		HRESULT createDeviceAndContext();
		void releaseDeviceAndContext();
		HRESULT createSwapChain();
		void releaseSwapChain();

		HRESULT createRenderTarget();
		HRESULT clearRenderTarget();

	private:
		std::vector<ID3D11InputLayout*> m_vInputLayouts;

	public:
		friend class RgGraphicsAPI;
	};


#pragma region Convert

	inline void ConvertRasterizerState(const RgRasterizerSettings& settings, D3D11_RASTERIZER_DESC& desc) {
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

	inline void ConvertDepthStencilState(const RgDepthStencilSettings& settings, D3D11_DEPTH_STENCIL_DESC& desc) {
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

#pragma endregion

}