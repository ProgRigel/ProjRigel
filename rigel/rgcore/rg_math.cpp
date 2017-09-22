#pragma once
#include "rgcore.h"
#include "rg_math.h"

namespace rg {
	template<typename T>
	std::string RgVec4<T>::toStr() const
	{
		std::stringstream ss;
		ss << "(" << x << "," << y << "," << z << "," << w << ")";
		return ss.str();
	}
	template<typename T>
	std::string RgVec3<T>::toStr() const
	{
		std::stringstream ss;
		ss << "(" << x << "," << y << "," << z << ")";
		return ss.str();
	}
	template<typename T>
	std::string RgVec2<T>::toStr() const
	{
		std::stringstream ss;
		ss << "(" << x << "," << y << ")";
		return ss.str();
	}
}


