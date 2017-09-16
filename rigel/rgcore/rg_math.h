#pragma once
#if defined(min)
#undef min
#endif
#if defined(max)
#undef max
#endif
#include <math.h>
namespace rg {
	typedef float RgFloat;
	struct RgVec2{
		RgFloat x, y;
		RgVec2(RgFloat _x,RgFloat _y):x(_x),y(_y){}
		RgVec2():x(0),y(0){}
		RgVec2(const RgVec2& v) :x(v.x), y(v.y) {}

		RgVec2& operator +=(RgFloat s) {
			x += s;
			y += s;
			return *this;
		}
		RgVec2& operator -=(RgFloat s) {
			x -= s;
			y -= s;
			return *this;
		}
		RgVec2& operator *=(RgFloat s) {
			x *= s;
			y *= s;
			return *this;
		}
		RgVec2& operator /=(RgFloat s) {
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
		//等等等等，一脸懵逼
		RgVec2& operator /=(const RgVec2& v) {
			x /= v.x;
			y /= v.y;
			return *this;
		}
		RgFloat dot(const RgVec2& v) {
			return x*v.x + y*v.y;
		}
		RgFloat length(){
			return sqrt(this->dot(*this));
		}
	};
	inline const RgFloat abs(RgFloat s) {
		return abs((float)s);
	}
	inline const RgVec2 operator+(const RgVec2& v1, const RgFloat& s) {
		return{ v1.x + s,v1.y + s };
	}
	inline const RgVec2 operator-(const RgVec2& v1, const RgFloat& s) {
		return{ v1.x - s,v1.y - s };
	}
	inline const RgVec2 operator*(const RgVec2& v1, const RgFloat& s) {
		return{ v1.x * s,v1.y * s };
	}
	inline const RgVec2 operator/(const RgVec2& v1, const RgFloat& s) {
		if (s != 0) {
			return{ v1.x / s,v1.y / s };
		}
		else{
			return v1;
		}
	}
	inline const RgVec2 operator+(const RgVec2& v1, const RgVec2& v2) {
		return{ v1.x + v2.x,v1.y + v2.y };
	}
	inline const RgVec2 operator-(const RgVec2& v1, const RgVec2& v2) {
		return{ v1.x - v2.x,v1.y - v2.y };
	}
	inline const RgVec2 operator*(const RgVec2& v1, const RgVec2& v2) {
		return{ v1.x * v2.x,v1.y * v2.y };
	}
	//等等
	inline const RgVec2 operator/(const RgVec2& v1, const RgVec2& v2) {
		return{ v1.x / v2.x,v1.y / v2.y };
	}
	inline const RgFloat dot(const RgVec2& v1, const RgVec2& v2) {
		return v1.x*v2.x + v1.y*v2.y;
	}
	inline const RgVec2 inverse(RgVec2 const& v){
		return { -v.x,-v.y };
	}
	inline const RgFloat length(RgVec2 const& v) {
		return sqrt(dot(v, v));
	}
	inline const RgVec2 min(RgVec2 const& v1, RgVec2 const& v2) {
		return length(v1) < length(v2) ? v1 : v2;
	}
	inline const RgVec2 max(RgVec2 const& v1, RgVec2 const& v2) {
		return length(v1) > length(v2) ? v1 : v2;
	}
	inline const RgVec2 abs(RgVec2 const& v){
		return { abs(v.x),abs(v.y) };
	}
	struct RgVec3 {
		RgFloat x = 0;
		RgFloat y = 0;
		RgFloat z = 0;
		RgVec3() :x(0), y(0), z(0) {}
		RgVec3(RgFloat _x, RgFloat _y, RgFloat _z) :x(_x), y(_y), z(_z){}
		inline RgVec3(const RgVec2& v) : x(v.x), y(v.y), z(0){}
	};

	struct RgVec4 {
		RgFloat x, y, z, w;
		RgVec4(RgFloat _x, RgFloat _y, RgFloat _z,RgFloat _w) :x(_x), y(_y), z(_z),w(_w) {}
	};



	inline const RgVec3 operator+(const RgVec3& v1, const RgVec3& v2) {
		return { v1.x + v2.x,v1.y + v2.y,v1.z + v2.z };
	}

	inline const RgVec4 operator+(const RgVec4& v1, const RgVec4& v2) {
		return{ v1.x + v2.x,v1.y + v2.y,v1.z + v2.z,v1.z+v2.z};
	}

	
	inline const RgVec3 operator-(const RgVec3& v1, const RgVec3& v2) {
		return{ v1.x - v2.x,v1.y - v2.y,v1.z - v2.z };
	}
	inline const RgVec4 operator-(const RgVec4& v1, const RgVec4& v2) {
		return{ v1.x - v2.x,v1.y - v2.y,v1.z - v2.z,v1.z - v2.z };
	}
	
	inline const RgFloat operator*(const RgVec3& v1, const RgVec3& v2) {
		return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
	}
	inline const RgFloat operator*(const RgVec4& v1, const RgVec4& v2) {
		return v1.w*v2.w + v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
	}

}