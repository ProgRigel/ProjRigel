#include "rg_render_context_dx11.h"

namespace rg {
	RgRenderContextDX11::RgRenderContextDX11()
	{
	}

	RgRenderContextDX11::~RgRenderContextDX11()
	{
		m_pDeviceContext = nullptr;
	}

}
