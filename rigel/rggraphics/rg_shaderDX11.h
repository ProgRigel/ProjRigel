#pragma once
#include "rg_shader.h"
#include <d3d11.h>

namespace rg {

	class RgGraphicsContextDX11;
	class RgShaderDX11 : public RgShader {

	public:
		RgShaderDX11(): RgShader(){}
		~RgShaderDX11();
		RgShaderDX11(RgShaderOptions options,ID3DBlob * shaderblob);

		void Release();

	public:
		ID3D11VertexShader * m_pVertexShader = nullptr;
		ID3D11PixelShader * m_pPixelShader = nullptr;
		ID3DBlob * m_pShaderBlob = nullptr;

		friend class RgGraphicsContextDX11;
	};
}