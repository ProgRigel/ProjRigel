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
	std::shared_ptr<RgBuffer> RgGraphicsContext::CraeteBuffer(RgBufferSettings settings)
	{
		return std::shared_ptr<RgBuffer>();
	}
	RgGraphicsContext::~RgGraphicsContext()
	{
	}
}

