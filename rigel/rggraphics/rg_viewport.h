#pragma once
#include <rgcore\rg_inc.h>
#include <rgcore\rg_math.h>

namespace rg {
	struct RgViewPort
	{
		RgVec2<RgFloat> TopLeft;
		RgVec2<RgFloat> Size;
		RgVec2<RgFloat> DepthMinMax;
	};
}