#pragma once
#include "rggraphics_inc.h"
#include "rg_graphicscontext.h"
#include "rg_rasterizer_state.h"

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
		virtual RgBuffer* CreateBuffer(RgBufferSettings settings);
		RgInputLayout * CreateInputLayout(const RgInputLayoutElement * elements,const unsigned int size, std::shared_ptr<RgShader> vertexShader);

		RgRenderContext * CreateDeferredContext();

		RgRasterizerState * CreateRasterizerState(const RgRasterizerSettings);

		void resizeBuffer(unsigned int width, unsigned int height);
		void render();
		void prerender();

	public:
		ID3D11RenderTargetView * GetRenderTargetView();
		ID3D11DepthStencilView * GetDepthStencilView();
		ID3D11DepthStencilState * GetDepthStencilState();

		const RgViewPort* GetViewPortDefault();


	private:
		

		ID3D11Device *m_pD3D11Device = nullptr;
		ID3D11DeviceContext *m_pD3D11DeviceContext = nullptr;
		IDXGISwapChain * m_pSwapChain = nullptr;
		
		ID3D11Texture2D * m_depthStencilBuffer = nullptr;
		ID3D11DepthStencilState *m_pdepthStencilState = nullptr;
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

#pragma endregion

}