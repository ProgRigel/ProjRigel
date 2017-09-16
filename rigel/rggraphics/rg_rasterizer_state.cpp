#include "rggraphics.h"
#include "rg_rasterizer_state.h"

namespace rg {
	RgRasterizerState::~RgRasterizerState()
	{
		Release();
		
	}
	void RgRasterizerState::Release()
	{
	}

	const RgRasterizerSettings & RgRasterizerState::GetSettings() const
	{
		return m_sSettings;
	}


}

