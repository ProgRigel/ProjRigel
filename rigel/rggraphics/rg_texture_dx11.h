#pragma once
#include "rg_texture.h"
namespace rg {


	class RgGraphicsContextDX11;
	class RgRenderContextDX11;

	class RgTextureDX11 : public RgTexture {

	public:
		RgTextureDX11(const RgTextureSettings& settings) :RgTexture(settings){}
		~RgTextureDX11();
		void Release();

	protected:
		ID3D11Texture2D * m_pd3d11tex2d = nullptr;
		ID3D11ShaderResourceView * m_psrv = nullptr;

		friend class RgGraphicsContextDX11;
		friend class RgRenderContextDX11;
	};
}