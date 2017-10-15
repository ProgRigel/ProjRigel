#pragma once
#include "rgcore.h"
#include "rg_math.h"

namespace rg {

	const RgVec2 RgVec2::Zero = RgVec2(0, 0);

	std::string RgVec4::toStr() const
	{
		std::stringstream ss;
		ss << "(" << x << "," << y << "," << z << "," << w << ")";
		return ss.str();
	}
	bool RgVec4::rect_contain(const RgVec2 & pos)
	{
		if (pos.x < x || pos.x > x + z) return false;
		if (pos.y < y || pos.y > y + w) return false;
		return true;
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


