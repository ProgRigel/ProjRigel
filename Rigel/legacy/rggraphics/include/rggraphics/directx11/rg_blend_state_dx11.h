#pragma once
#include "rg_blend_state.h"
namespace rg {

	class RgGraphicsContextDX11;
	class RgBlendStateDX11 : public RgBlendState {

	public:
		RgBlendStateDX11(const RgBlendStateSettings& settings):RgBlendState(settings){}
		~RgBlendStateDX11();
		void Release();

	private:
		ID3D11BlendState * m_ptr = nullptr;

		friend class RgGraphicsContextDX11;
		friend class RgRenderContextDX11;
	};
}