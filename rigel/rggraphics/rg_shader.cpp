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
	}
	RG_SHADER_ENTRY RgShader::GetShaderEntry()
	{
		return m_sShaderOptions.ShaderEntry;
	}
}


