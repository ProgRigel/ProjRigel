#pragma once

namespace rg {
	typedef float RgScalar;
	struct RgVec2{
		RgScalar x, y;
		RgVec2(RgScalar _x,RgScalar _y):x(_x),y(_y){}
		RgVec2():x(0),y(0){}
		RgVec2(const RgVec2& v) :x(v.x), y(v.y) {}

		RgVec2& operator +=(RgScalar s) {
			x += s;
			y += s;
			return *this;
		}
		RgVec2& operator -=(RgScalar s) {
			x -= s;
			y -= s;
			return *this;
		}
		RgVec2& operator *=(RgScalar s) {
			x *= s;
			y *= s;
			return *this;
		}
		RgVec2& operator /=(RgScalar s) {
			if (s != 0) {
				x /= s;
				y /= s;
				return *this;
			}
			return *this;
		}
		RgVec2& operator +=(const RgVec2& v){
			x += v.x;
			y += v.y;
			return *this;
		}
		RgVec2& operator -=(const RgVec2& v) {
			x -= v.x;
			y -= v.y;
			return *this;
		}
		RgVec2& operator *=(const RgVec2& v) {
			x *= v.x;
			y *= v.y;
			return *this;
		}
		
	};

	struct RgVec3 {
		RgScalar x = 0;
		RgScalar y = 0;
		RgScalar z = 0;
		RgVec3() :x(0), y(0), z(0) {}
		RgVec3(RgScalar _x, RgScalar _y, RgScalar _z) :x(_x), y(_y), z(_z){}
		inline RgVec3(const RgVec2& v) : x(v.x), y(v.y), z(0){}
	};

	struct RgVec4 {
		RgScalar x, y, z, w;
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
	inline const RgScalar operator*(const RgVec2& v1, const RgVec2& v2) {
		return v1.x*v2.x + v1.y*v2.y;
	}
	inline const RgScalar operator*(const RgVec3& v1, const RgVec3& v2) {
		return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
	}
	inline const RgScalar operator*(const RgVec4& v1, const RgVec4& v2) {
		return v1.w*v2.w + v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
	}
}