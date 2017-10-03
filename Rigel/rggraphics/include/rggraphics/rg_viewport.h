#pragma once
#include <rgcore\rg_inc.h>
#include <rgcore\rg_math.h>

namespace rg {
	struct RgViewPort
	{
		RgVec2 TopLeft;
		RgVec2 Size;
		RgVec2 DepthMinMax;
	};
}