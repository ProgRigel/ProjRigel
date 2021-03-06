#include "rggraphics.h"
#include "rg_shader.h"

namespace rg {
	RgShader::RgShader()
	{
	}
	RgShader::RgShader(RgShaderOptions & options)
	{
		m_sShaderOptions = options;
	}
	RgShader::~RgShader()
	{
		Release();
	}
	void RgShader::Release()
	{

	}
	RG_SHADER_ENTRY RgShader::GetShaderEntry()
	{
		return m_sShaderOptions.ShaderEntry;
	}
}


