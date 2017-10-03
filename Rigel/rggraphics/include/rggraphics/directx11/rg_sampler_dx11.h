#pragma once
#include "rg_sampler.h"
namespace rg {

	class RgGraphicsContextDX11;
	class RgRenderContextDX11;

	class RgGraphicsSamplerDX11 : public RgGraphicsSampler {
	public:
		RgGraphicsSamplerDX11(const RgGraphicsSamplerSettings& settings) :RgGraphicsSampler(settings){}
		~RgGraphicsSamplerDX11();
		void Release();

	protected:
		ID3D11SamplerState * m_psampler = nullptr;

		friend class RgGraphicsContextDX11;
		friend class RgRenderContextDX11;
	};
}