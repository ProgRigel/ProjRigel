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
	std::string RgVec3::toStr() const
	{
		std::stringstream ss;
		ss << "(" << x << "," << y << "," << z << ")";
		return ss.str();
	}
	std::string RgVec2::toStr() const
	{
		std::stringstream ss;
		ss << "(" << x << "," << y << ")";
		return ss.str();
	}

	const RgVec4 RgVec4::Zero = RgVec4();
}


