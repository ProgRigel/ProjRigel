#include "rggraphics.h"
#include <d3d11.h>
#include "rg_shader.h"
#include "rg_shaderDX11.h"

namespace rg {
	RgShaderDX11::~RgShaderDX11()
	{
		Release();
	}
	RgShaderDX11::RgShaderDX11(RgShaderOptions options, ID3DBlob * shaderblob)
	{
		m_sShaderOptions = options;
		m_pShaderBlob = shaderblob;
	}
	void RgShaderDX11::Release()
	{
		if (m_pShaderBlob) {
			m_pShaderBlob->Release();
			m_pShaderBlob = nullptr;
		}
		if (m_pVertexShader) m_pVertexShader->Release();
		m_pVertexShader = nullptr;
		if (m_pPixelShader) m_pPixelShader->Release();
		m_pPixelShader = nullptr;
	}
}

