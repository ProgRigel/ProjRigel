#pragma once

namespace rg {

	struct RgVec2{
		float x, y;
		RgVec2(float _x,float _y):x(_x),y(_y){}
		RgVec2():x(0),y(0){}
	};

	struct RgVec3 {
		float x = 0;
		float y = 0;
		float z = 0;
		RgVec3() :x(0), y(0), z(0) {}
		RgVec3(float _x, float _y, float _z) :x(_x), y(_y), z(_z){}
		inline RgVec3(const RgVec2& v) : x(v.x), y(v.y), z(0){}
	};

	struct RgVec4 {
		float x, y, z, w;
	};

	inline const RgVec2 operator+(const RgVec2& v1, const RgVec2& v2) {
		return{ v1.x + v2.x,v1.y + v2.y };
	}

	inline const RgVec3 operator+(const RgVec3& v1, const RgVec3& v2) {
		return { v1.x + v2.x,v1.y + v2.y,v1.z + v2.z };
	}

	inline const RgVec4 operator+(const RgVec4& v1, const RgVec4& v2) {
		return{ v1.x + v2.x,v1.y + v2.y,v1.z + v2.z,v1.z+v2.z};
	}

	inline const RgVec2 operator-(const RgVec2& v1, const RgVec2& v2) {
		return{ v1.x - v2.x,v1.y - v2.y };
	}
	inline const RgVec3 operator-(const RgVec3& v1, const RgVec3& v2) {
		return{ v1.x - v2.x,v1.y - v2.y,v1.z - v2.z };
	}
	inline const RgVec4 operator-(const RgVec4& v1, const RgVec4& v2) {
		return{ v1.x - v2.x,v1.y - v2.y,v1.z - v2.z,v1.z - v2.z };
	}
	inline const float operator*(const RgVec2& v1, const RgVec2& v2) {
		return v1.x*v2.x + v1.y*v2.y;
	}
	inline const float operator*(const RgVec3& v1, const RgVec3& v2) {
		return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
	}
	inline const float operator*(const RgVec4& v1, const RgVec4& v2) {
		return v1.w*v2.w + v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
	}
}