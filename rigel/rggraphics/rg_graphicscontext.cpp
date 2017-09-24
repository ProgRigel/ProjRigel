#include "rggraphics.h"
#include "rg_graphicscontext.h"
#include "rg_render_context.h"
#include "rg_shader.h"
#include "rg_texture.h"
#include "rg_buffer.h"
#include "rg_material.h"
#include "rg_rasterizer_state.h"
#include "rg_sampler.h"

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
	RgRasterizerState * RgGraphicsContext::CreateRasterizerState(const RgRasterizerSettings settings)
	{
		return nullptr;
	}
	RgDepthStencilState * RgGraphicsContext::CreateDepthStencilState(const RgDepthStencilSettings &)
	{
		return nullptr;
	}
	RgGraphicsSampler * RgGraphicsContext::CreateSampler(const RgGraphicsSamplerSettings &)
	{
		return nullptr;
	}
	RgRenderTarget * RgGraphicsContext::GetRenderTarget()
	{
		return m_pRenderTarget;
	}
	RgRenderContext * RgGraphicsContext::GetRenderContext()
	{
		return m_pRenderContext;
	}
	const RgViewPort* RgGraphicsContext::GetViewPortDefault()
	{
		return nullptr;
	}
	RgGraphicsContext::~RgGraphicsContext()
	{
		release();
	}
	void RgGraphicsContext::release()
	{
		for (auto rs : m_vRasterState) {
			if (rs != nullptr) {
				rs->Release();
				delete rs;
				rs = nullptr;
			}
		}

		for each (auto buffer in m_vBuffers)
		{
			if (buffer) {
				buffer->Release();
				delete buffer;
			}
		}

		for each (auto ctx in m_vRenderContexts)
		{
			ctx->Release();
			delete ctx;
			ctx = nullptr;
		}
		std::vector<RgRenderContext*>().swap(m_vRenderContexts);


		for (auto tex : m_vTexture) {
			tex->Release();
		}
		std::vector<std::shared_ptr<RgTexture>>().swap(m_vTexture);

		for (auto sampler : m_vSampler) {
			sampler->Release();
			sampler = nullptr;
		}
		std::vector<RgGraphicsSampler*>().swap(m_vSampler);

		if (m_pRenderContext != nullptr) {
			m_pRenderContext->Release();
			delete m_pRenderContext;
			m_pRenderContext = nullptr;
		}
	}
}

