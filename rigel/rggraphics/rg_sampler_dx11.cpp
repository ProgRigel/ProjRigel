#include "rggraphics.h"
#include "rg_sampler_dx11.h"

namespace rg {
	RgGraphicsSamplerDX11::~RgGraphicsSamplerDX11()
	{
		Release();
	}
	void RgGraphicsSamplerDX11::Release()
	{
		if (m_psampler != nullptr) {
			m_psampler->Release();
			m_psampler = nullptr;
		}
	}
}

