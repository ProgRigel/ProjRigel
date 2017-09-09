#pragma once
#include <rgcore\rgcore.h>
#include <Windows.h>
#include <memory>
#include <vector>

#include "rg_shader.h"
#include "rg_texture.h"
#include "rg_material.h"
#include "rg_buffer.h"

namespace rg {

	class RgBuffer;
	class RgMaterial;
	class RgShader;
	class RgTexture;
	class RgRenderContext;
	class RgInputLayout;
	struct RgInputLayoutElement;


	struct RgBufferSettings;

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

		virtual std::shared_ptr<RgShader> CompileShaderFromFile(std::wstring filepath, RgShaderOptions& options);
		virtual std::shared_ptr<RgShader> CompileShaderFromSource(std::wstring source, RgShaderOptions& options);
		virtual std::shared_ptr<RgTexture> CreateTexture(RgTextureSettings& settings);
		virtual std::shared_ptr<RgMaterial> CreateMaterial(std::shared_ptr<RgShader> shader);

		virtual RgInputLayout * CreateInputLayout(const RgInputLayoutElement * elements, const unsigned int size,std::shared_ptr<RgShader> vertexShader) = 0;

		virtual RgBuffer* CreateBuffer(RgBufferSettings settings);

		RgRenderContext* GetRenderContext();
		
	protected:
		virtual ~RgGraphicsContext();
		virtual void init(RG_GRAPHICS_INIT_SETTINGS * settings) = 0;
		virtual void release() = 0;

		RgGraphicsContext(const RgGraphicsContext&) = delete;
		const RgGraphicsContext& operator=(const RgGraphicsContext&) = delete;

	protected:
		RG_GRAPHICS_INIT_SETTINGS m_settings;
		std::vector<RgBuffer*> m_vBuffers;

		RgRenderContext *m_pRenderContext = nullptr;

	public:
		friend class RgGraphicsAPI;
	};
}
