#pragma once
#include "rg_texture.h"
namespace rg {


	class RgGraphicsContextDX11;
	class RgTextureDX11 : public RgTexture {

	public:
		RgTextureDX11(const RgTextureSettings& settings) :RgTexture(settings){}
		~RgTextureDX11();
		void Release();

	protected:
		ID3D11Texture2D * m_pd3d11tex2d = nullptr;

		friend class RgGraphicsContextDX11;
	};
}