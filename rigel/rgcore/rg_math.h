#pragma once

namespace rg {

	typedef struct {
		float x, y;
	} RgVec2;

	typedef struct {
		float x, y, z;
	}RgVec3;

	typedef struct {
		float x, y, z, w;
	}RgVec4;

	inline const RgVec2& operator+(const RgVec2& v1, const RgVec2& v2) {
		return{ v1.x + v2.x,v1.y + v2.y };
	}

	inline const RgVec3& operator+(const RgVec3& v1, const RgVec3& v2) {
		return{ v1.x + v2.x,v1.y + v2.y,v1.z + v2.z };
	}

	inline const RgVec4& operator+(const RgVec4& v1, const RgVec4& v2) {
		return{ v1.x + v2.x,v1.y + v2.y,v1.z + v2.z,v1.z+v2.z};
	}

	inline const RgVec2& operator-(const RgVec2& v1, const RgVec2& v2) {
		return{ v1.x - v2.x,v1.y - v2.y };
	}
	inline const RgVec3& operator-(const RgVec3& v1, const RgVec3& v2) {
		return{ v1.x - v2.x,v1.y - v2.y,v1.z - v2.z };
	}
	inline const RgVec4& operator-(const RgVec4& v1, const RgVec4& v2) {
		return{ v1.x - v2.x,v1.y - v2.y,v1.z - v2.z,v1.z - v2.z };
	}
}