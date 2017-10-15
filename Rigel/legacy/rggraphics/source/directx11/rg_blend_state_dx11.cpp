#include "rggraphics.h"
#include "directx11\rg_blend_state_dx11.h"

namespace rg {
	RgBlendStateDX11::~RgBlendStateDX11()
	{
		Release();
	}
	void RgBlendStateDX11::Release()
	{
		if (m_ptr != nullptr) {
			m_ptr->Release();
			m_ptr = nullptr;
		}
	}
}


