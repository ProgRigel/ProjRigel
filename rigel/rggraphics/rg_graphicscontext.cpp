#include "rg_graphicscontext.h"


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
	std::shared_ptr<RgBuffer> RgGraphicsContext::CreateBuffer(RgBufferSettings settings)
	{
		return std::shared_ptr<RgBuffer>();
	}
	RgGraphicsContext::~RgGraphicsContext()
	{
		//release buffers
		for each (auto buffer in m_vBuffers)
		{
			buffer.reset();
		}

		if (m_pRenderContext != nullptr) {
			delete m_pRenderContext;
			m_pRenderContext = nullptr;
		}
	}
}

