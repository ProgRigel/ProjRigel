#include "rg_shaderDX11.h"

namespace rg {
	RgShaderDX11::~RgShaderDX11()
	{
		if (m_pVertexShader) m_pVertexShader->Release();
		m_pVertexShader = nullptr;
	}
	RgShaderDX11::RgShaderDX11(RgShaderOptions options, ID3D11VertexShader * shader)
	{
		m_sShaderOptions = options;
		m_pVertexShader = shader;
	}
}

