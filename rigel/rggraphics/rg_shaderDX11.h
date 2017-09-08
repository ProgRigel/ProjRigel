#pragma once
#include "rg_shader.h"
#include <d3d11.h>

namespace rg {

	class RgShaderDX11 : public RgShader {

	public:
		RgShaderDX11(): RgShader(){}
		~RgShaderDX11();
		RgShaderDX11(RgShaderOptions options, ID3D11VertexShader * shader);

	protected:
		ID3D11VertexShader * m_pVertexShader;
	};
}