#include "rggraphics.h"
#include "rg_graphicscontext.h"
#include "rg_render_context.h"
#include "rg_shader.h"
#include "rg_texture.h"
#include "rg_buffer.h"
#include "rg_material.h"

namespace rg {
	RgGraphicsContext::RgGraphicsContext()
	{
	}
	void RgGraphicsContext::resizeBuffer(unsigned int width, unsigned int height)
	{
	}
	void RgGraphicsContext::render()
	{
	}
	void RgGraphicsContext::prerender()
	{
	}
	std::shared_ptr<RgShader> RgGraphicsContext::GetCachedShader(std::wstring shaderId)
	{
		std::unordered_map<std::wstring, std::shared_ptr<RgShader>>::iterator iter;
		iter = m_mShaderCaches.find(shaderId);
		if (iter != m_mShaderCaches.end()) {
			return (*iter).second;
		}

		return nullptr;
	}
	std::shared_ptr<RgShader> RgGraphicsContext::CompileShaderFromFile(std::wstring filepath, RgShaderOptions & options)
	{
		return std::make_shared<RgShader>();
	}
	std::shared_ptr<RgShader> RgGraphicsContext::CompileShaderFromSource(std::wstring source, RgShaderOptions & options)
	{
		return std::shared_ptr<RgShader>();
	}
	std::shared_ptr<RgTexture> RgGraphicsContext::CreateTexture(RgTextureSettings & settings)
	{
		return std::make_shared<RgTexture>();
	}
	std::shared_ptr<RgMaterial> RgGraphicsContext::CreateMaterial(std::shared_ptr<RgShader> shader)
	{
		return std::make_shared<RgMaterial>();
	}
	RgBuffer* RgGraphicsContext::CreateBuffer(RgBufferSettings settings)
	{
		return nullptr;
	}
	RgRenderContext * RgGraphicsContext::GetRenderContext()
	{
		return m_pRenderContext;
	}
	RgGraphicsContext::~RgGraphicsContext()
	{
		//release buffers
		for each (auto buffer in m_vBuffers)
		{
			if (buffer) {
				buffer->Release();
				delete buffer;
			}
		}

		for each (auto ctx in m_vRenderContexts)
		{
			delete ctx;
			ctx = nullptr;
		}
		std::vector<RgRenderContext*>().swap(m_vRenderContexts);

		if (m_pRenderContext != nullptr) {
			delete m_pRenderContext;
			m_pRenderContext = nullptr;
		}
	}
}

