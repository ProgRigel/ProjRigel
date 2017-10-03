#include "rggraphics.h"
#include "directx11\rg_depthstencil_state_dx11.h"

namespace rg {
	RgDepthStencilStateDX11::~RgDepthStencilStateDX11()
	{
	}

	void RgDepthStencilStateDX11::Release()
	{
		if (m_state != nullptr) {
			m_state->Release();
			m_state = nullptr;
		}
	}

}

