#pragma once
#include "rggraphics_inc.h"
#include <rggraphics\rggraphics.h>
namespace rg {

	class RgBuffer;
	class RgMaterial;
	class RgShader;
	class RgTexture;
	class RgRenderContext;
	class RgInputLayout;

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

		virtual std::shared_ptr<RgShader> CompileShaderFromFile(std::wstring filepath, RgShaderOptions& options);
		virtual std::shared_ptr<RgShader> CompileShaderFromSource(std::wstring source, RgShaderOptions& options);
		virtual std::shared_ptr<RgTexture> CreateTexture(RgTextureSettings& settings);
		virtual std::shared_ptr<RgMaterial> CreateMaterial(std::shared_ptr<RgShader> shader);

		virtual RgInputLayout * CreateInputLayout(const RgInputLayoutElement * elements, const unsigned int size,std::shared_ptr<RgShader> vertexShader) = 0;

		virtual RgBuffer* CreateBuffer(RgBufferSettings settings);

		RgRenderContext* GetRenderContext();
		virtual RgRenderContext * CreateDeferredContext() = 0;
		
	protected:
		virtual ~RgGraphicsContext();
		virtual void init(RG_GRAPHICS_INIT_SETTINGS * settings) = 0;
		virtual void release() = 0;

		RgGraphicsContext(const RgGraphicsContext&) = delete;
		const RgGraphicsContext& operator=(const RgGraphicsContext&) = delete;

	protected:
		RG_GRAPHICS_INIT_SETTINGS m_settings;
		std::vector<RgBuffer*> m_vBuffers;
		std::vector<RgRenderContext *> m_vRenderContexts;

		RgRenderContext *m_pRenderContext = nullptr;

	public:
		friend class RgGraphicsAPI;
	};
}
