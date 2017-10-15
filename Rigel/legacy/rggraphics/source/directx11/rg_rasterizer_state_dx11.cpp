#include "rggraphics.h"
#include "directx11\rg_rasterizer_state_dx11.h"


namespace rg {
	RgRasterizerStateDX11::~RgRasterizerStateDX11()
	{
		Release();
	}

	void RgRasterizerStateDX11::Release()
	{
		if (m_ptr != nullptr) {
			m_ptr->Release();
			m_ptr = nullptr;
		}
	}
}


