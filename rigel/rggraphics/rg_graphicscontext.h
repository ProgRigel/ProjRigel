#pragma once
#include "rggraphics_inc.h"
#include <rggraphics\rggraphics.h>
#include <rgcore\rg_signal.hpp>
namespace rg {

	class RgBuffer;
	class RgMaterial;
	class RgShader;
	class RgTexture;
	class RgRenderContext;
	class RgInputLayout;
	class RgRasterizerState;
	class RgDepthStencilState;
	class RgRenderTarget;
	class RgGraphicsSampler;

	struct RG_GRAPHICS_INIT_SETTINGS
	{
		unsigned int BufferWidth = 0;
		unsigned int BufferHeight = 0;
		bool Windowed = true;
		HWND OutputWindow = nullptr;
	};


	class RgGraphicsContext
	{
	public:
		RgGraphicsContext();

		virtual void resizeBuffer(unsigned int width, unsigned int height);
		virtual void render();
		virtual void prerender();

		std::shared_ptr<RgShader> GetCachedShader(std::wstring shaderId);

		virtual std::shared_ptr<RgShader> CompileShaderFromFile(std::wstring filepath, RgShaderOptions& options);
		virtual std::shared_ptr<RgShader> CompileShaderFromSource(std::wstring source, RgShaderOptions& options);
		virtual std::shared_ptr<RgTexture> CreateTexture(RgTextureSettings& settings);
		virtual std::shared_ptr<RgMaterial> CreateMaterial(std::shared_ptr<RgShader> shader);

		virtual RgInputLayout * CreateInputLayout(const RgInputLayoutElement * elements, const unsigned int size,std::shared_ptr<RgShader> vertexShader) = 0;

		virtual RgBuffer* CreateBuffer(RgBufferSettings settings);
		virtual RgRasterizerState * CreateRasterizerState(const RgRasterizerSettings);
		virtual RgDepthStencilState* CreateDepthStencilState(const RgDepthStencilSettings&);
		virtual RgGraphicsSampler* CreateSampler(const RgGraphicsSamplerSettings&);

		RgRenderTarget * GetRenderTarget();
		RgRenderContext* GetRenderContext();
		virtual const RgViewPort* GetViewPortDefault();
		virtual RgRenderContext * CreateDeferredContext() = 0;
		
	protected:
		virtual ~RgGraphicsContext();
		virtual void init(RG_GRAPHICS_INIT_SETTINGS * settings) = 0;
		virtual void release();

		RgGraphicsContext(const RgGraphicsContext&) = delete;
		const RgGraphicsContext& operator=(const RgGraphicsContext&) = delete;

	protected:
		RG_GRAPHICS_INIT_SETTINGS m_settings;
		std::vector<RgBuffer*> m_vBuffers;
		std::vector<RgRenderContext *> m_vRenderContexts;
		std::vector<RgRasterizerState*> m_vRasterState;
		std::vector<RgDepthStencilState*> m_vDepthStencilState;
		std::vector<std::shared_ptr<RgTexture>> m_vTexture;
		std::vector<RgGraphicsSampler*> m_vSampler;

		std::unordered_map<std::wstring, std::shared_ptr<RgShader>> m_mShaderCaches;
		

		RgRenderContext *m_pRenderContext = nullptr;
		RgRenderTarget * m_pRenderTarget = nullptr;

	public:

		Signal<void()> EventBeforeResize;
		Signal<void(unsigned int,unsigned int)> EventAfterResize;
		Signal<void()> EventRelease;

		friend class RgGraphicsAPI;
	};
}
