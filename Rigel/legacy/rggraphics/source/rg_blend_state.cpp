#include "rggraphics.h"
#include "rg_blend_state.h"

namespace rg {
	RgBlendState::~RgBlendState()
	{
		Release();
	}

	void RgBlendState::Release()
	{
	}

}
