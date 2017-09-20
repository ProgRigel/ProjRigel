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
	template<typename T>
	struct RgVec2{
		T x, y;
		RgVec2(int _x, int _y) :x((float)_x), y((float)_y){}
		RgVec2(T _x,T _y):x(_x),y(_y){}
		RgVec2():x(0),y(0){}
		RgVec2(const RgVec2<T>& v) :x(v.x), y(v.y) {}

		RgVec2& operator +=(T s) {
			x += s;
			y += s;
			return *this;
		}
		RgVec2& operator -=(T s) {
			x -= s;
			y -= s;
			return *this;
		}
		RgVec2& operator *=(T s) {
			x *= s;
			y *= s;
			return *this;
		}
		RgVec2& operator /=(T s) {
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

		std::string toStr() const;
	};
	inline const RgFloat abs(RgFloat s) {
		return abs((float)s);
	}
	template<typename T>
	inline const RgVec2<T> operator+(const RgVec2<T>& v1, const RgFloat& s) {
		return{ v1.x + s,v1.y + s };
	}
	template<typename T>
	inline const RgVec2<T> operator-(const RgVec2<T>& v1, const RgFloat& s) {
		return{ v1.x - s,v1.y - s };
	}
	template<typename T>
	inline const RgVec2<T> operator*(const RgVec2<T>& v1, const RgFloat& s) {
		return{ v1.x * s,v1.y * s };
	}
	template<typename T>
	inline const RgVec2<T> operator/(const RgVec2<T>& v1, const RgFloat& s) {
		if (s != 0) {
			return{ v1.x / s,v1.y / s };
		}
		else{
			return v1;
		}
	}
	template<typename T>
	inline const RgVec2<T> operator+(const RgVec2<T>& v1, const RgVec2<T>& v2) {
		return{ v1.x + v2.x,v1.y + v2.y };
	}
	template<typename T>
	inline const RgVec2<T> operator-(const RgVec2<T>& v1, const RgVec2<T>& v2) {
		return{ v1.x - v2.x,v1.y - v2.y };
	}
	template<typename T>
	inline const RgVec2<T> operator*(const RgVec2<T>& v1, const RgVec2<T>& v2) {
		return{ v1.x * v2.x,v1.y * v2.y };
	}
	//等等
	template<typename T>
	inline const RgVec2<T> operator/(const RgVec2<T>& v1, const RgVec2<T>& v2) {
		return{ v1.x / v2.x,v1.y / v2.y };
	}
	template<typename T>
	inline const RgFloat dot(const RgVec2<T>& v1, const RgVec2<T>& v2) {
		return v1.x*v2.x + v1.y*v2.y;
	}
	template<typename T>
	inline const RgVec2<T> inverse(RgVec2<T> const& v){
		return { -v.x,-v.y };
	}
	template<typename T>
	inline const RgFloat length(RgVec2<T> const& v) {
		return sqrt(dot(v, v));
	}
	template<typename T>
	inline const RgVec2 min(RgVec2<T> const& v1, RgVec2<T> const& v2) {
		return length(v1) < length(v2) ? v1 : v2;
	}
	template<typename T>
	inline const RgVec2<T> max(RgVec2<T> const& v1, RgVec2<T> const& v2) {
		return length(v1) > length(v2) ? v1 : v2;
	}
	template<typename T>
	inline const RgVec2<T> abs(RgVec2<T> const& v){
		return { abs(v.x),abs(v.y) };
	}
	template<typename T>
	struct RgVec3 {
		T x = 0;
		T y = 0;
		T z = 0;
		RgVec3(int _x, int _y, int _z) :x((float)_x), y((float)_y), z((float)_z) {}
		RgVec3() :x(0), y(0), z(0) {}
		RgVec3(T _x, T _y, T _z) :x(_x), y(_y), z(_z){}
		inline RgVec3(const RgVec2<T>& v) : x(v.x), y(v.y), z(0){}
		std::string toStr() const;
		RgVec3& operator +=(T s) {
			x += s;
			y += s;
			z += s;
			return *this;
		}
		RgVec3& operator -=(T s) {
			x -= s;
			y -= s;
			z -= s;
			return *this;
		}
		RgVec3& operator *=(T s) {
			x *= s;
			y *= s;
			z *= s;
			return *this;
		}
		RgVec3& operator /=(T s) {
			if (s != 0)
			{
				x /= s;
				y /= s;
				z /= s;
				return *this;
			}
			return *this;
		}
		RgVec3& operator +=(T v) {
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}
		RgVec3& operator -=(T v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}
		RgVec3& operator *=(T v) {
			x *= v.x;
			y *= v.y;
			z *= v.z;
			return *this;
		}
		RgVec3& operator /=(T v) {
			x /= v.x;
			y /= v.y;
			z /= v.z;
			return *this;
		}
		RgFloat dot(const T& v) {
			return x*v.x + y*v.y + z*v.z;
		}
		RgFloat length() {
			return sqrt(this->dot(*this));
		}
	};
	template<typename T>
	struct RgVec4 {
		T x, y, z, w;
		RgVec4(int _x,int _y,int _z,int _w):x((float)_x),y((float)_y),z((float)_z),w((float)_w){}
		RgVec4(RgFloat _x, RgFloat _y, RgFloat _z,RgFloat _w) :x(_x), y(_y), z(_z),w(_w) {}
		RgVec4():x(0),y(0),z(0),w(0){}
		RgVec4(const RgVec2<T>& v1,const RgVec2<T>& v2):x(v1.x),y(v1.y),z(v2.x),w(v2.y){}
		RgVec4(const RgVec2<T>& v1, T _z,T _w) :x(v1.x), y(v1.y), z(_z), w(_w) {}
		std::string toStr() const;

		inline const RgVec3 xyz() const{
			return RgVec3(x, y, z);
		}

		RgVec4& operator=(const RgVec2& v) {
			this->x = v.x;
			this->y = v.y;
			this->z = 0;
			this->w = 0;
			return *this;
		}
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


	struct RgMatrix3x3 {
		RgVec3 m1;
		RgVec3 m2;
		RgVec3 m3;
	};
	
	struct RgMatrix4x4 {
		RgVec4 m1;
		RgVec4 m2;
		RgVec4 m3;
		RgVec4 m4;
	};

}