#pragma once
#include <rgcore\rg_math.h>
#include "rggraphics_inc.h"

#include "rg_graphicsAPI.h"

namespace rg {

	struct RgGraphicsDisplayMode
	{
		unsigned int Width;
		unsigned int Height;
		unsigned int RefreshRateNumerator;
		unsigned int RefreshRateDenominator;
	};
}