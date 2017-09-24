#include "rggraphics.h"
#include "rg_texture_dx11.h"

namespace rg {
	RgTextureDX11::~RgTextureDX11()
	{
		Release();
	}
	void RgTextureDX11::Release()
	{
		if (m_pd3d11tex2d != nullptr) {
			m_pd3d11tex2d->Release();
			m_pd3d11tex2d = nullptr;
		}
	}
}

