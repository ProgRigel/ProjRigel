#pragma once
#include "rgcore.h"
#include "rg_math.h"

namespace rg {
	std::string RgVec4::toStr() const
	{
		std::stringstream ss;
		ss << "(" << x << "," << y << "," << z << "," << w << ")";
		return ss.str();
	}
}


