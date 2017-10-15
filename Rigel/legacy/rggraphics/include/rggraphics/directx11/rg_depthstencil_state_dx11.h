#pragma once
#include "rg_depthstencil_state.h"
#include <d3d11.h>
namespace rg {

	class RgGraphicsContextDX11;
	class RgRenderContextDX11;

	class RgDepthStencilStateDX11 : public RgDepthStencilState {
	public:
		RgDepthStencilStateDX11(const RgDepthStencilSettings& settings) :RgDepthStencilState(settings) {

		}
		~RgDepthStencilStateDX11();

		void Release();

	protected:
		ID3D11DepthStencilState * m_state = nullptr;

		friend class RgGraphicsContextDX11;
		friend class RgRenderContextDX11;
	};
}