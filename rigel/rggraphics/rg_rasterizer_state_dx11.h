#pragma once
#include "rg_rasterizer_state.h"

namespace rg {
	class RgGraphicsContextDX11;
	class RgRasterizerStateDX11 :public RgRasterizerState {

	public:
		~RgRasterizerStateDX11();
		void Release();

	private:
		RgRasterizerStateDX11(const RgRasterizerSettings& settings):RgRasterizerState(settings){}
		ID3D11RasterizerState * m_ptr = nullptr;

		friend class RgGraphicsContextDX11;
		friend class RgRenderContextDX11;
	};
}