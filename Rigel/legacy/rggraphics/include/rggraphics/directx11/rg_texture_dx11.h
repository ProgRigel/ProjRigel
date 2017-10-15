#pragma once
#include "rg_texture.h"
namespace rg {


	class RgGraphicsContextDX11;
	class RgRenderContextDX11;
	class RgRenderContext;

	class RgTextureDX11 : public RgTexture {

	public:
		RgTextureDX11(const RgTextureSettings& settings) :RgTexture(settings){}
		void SetRawData(void* data, unsigned int length);
		void SetData(RgRenderContext * renderctx,void * data,size_t size);
		~RgTextureDX11();
		void Release();

	protected:
		ID3D11Texture2D * m_pd3d11tex2d = nullptr;
		ID3D11ShaderResourceView * m_psrv = nullptr;

		friend class RgGraphicsContextDX11;
		friend class RgRenderContextDX11;
	};
}