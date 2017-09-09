#include "rg_shaderDX11.h"

namespace rg {
	RgShaderDX11::~RgShaderDX11()
	{
		if(m_pShaderBlob){
			m_pShaderBlob->Release();
			m_pShaderBlob = nullptr;
		}
		if (m_pVertexShader) m_pVertexShader->Release();
		m_pVertexShader = nullptr;
		if (m_pPixelShader) m_pPixelShader->Release();
		m_pPixelShader = nullptr;
	}
	RgShaderDX11::RgShaderDX11(RgShaderOptions options, ID3DBlob * shaderblob)
	{
		m_sShaderOptions = options;
		m_pShaderBlob = shaderblob;
	}
}

