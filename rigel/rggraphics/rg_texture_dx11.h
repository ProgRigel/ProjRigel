#pragma once
#include "rg_texture.h"
namespace rg {

	class RgTextureDX11 : public RgTexture {

	public:
		RgTextureDX11(const RgTextureSettings& settings) :RgTexture(settings){}
		~RgTextureDX11();
		void Release();
	};
}