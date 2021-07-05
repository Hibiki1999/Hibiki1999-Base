#ifndef VEC3_H_
#define VEC3_H_

#include <cmath>
#include <DxLib.h>

#include "../../MyMath/MyMath.h"

struct Vec3
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	Vec3() = default;

	Vec3(float _x, float _y, float _z) :x(_x), y(_y), z(_z) {}

	Vec3 operator +(const Vec3& other) const // 2€ +
	{
		return{ x + other.x, y + other.y,z + other.z };
	}

	Vec3 operator -(const Vec3& other) const // 2€ -
	{
		return{ x - other.x, y - other.y,z - other.z };
	}

	Vec3 operator *(float s) const // 2€ *
	{
		return{ x * s, y * s,z * s };
	}

	Vec3 operator *(Vec3 s) const // 2€ *
	{
		return{ x * s.x, y * s.y,z * s.z };
	}

	Vec3 operator /(float s) const // 2€ /
	{
		return{ x / s, y / s ,z / s };
	}

	Vec3& operator +=(const Vec3& other) // •¡‡‘ã“ü‰‰ŽZ +=
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vec3& operator -=(const Vec3& other) // •¡‡‘ã“ü‰‰ŽZ -=
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vec3& operator *=(float s) // •¡‡‘ã“ü‰‰ŽZ *=
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	Vec3& operator *=(Vec3 s) // •¡‡‘ã“ü‰‰ŽZ *=
	{
		x *= s.x;
		y *= s.y;
		z *= s.z;
		return *this;
	}

	Vec3& operator /=(float s) // •¡‡‘ã“ü‰‰ŽZ /=
	{
		if (s != 0)
		{
			this->x /= s;
			this->y /= s;
			this->z /= s;
		}
		return *this;
	}

	bool operator ==(const Vec3& other) //“ñ‚Â‚ÌƒxƒNƒgƒ‹‚ª“¯‚¶‚©‚Ç‚¤‚©‚ð”»•Ê‚·‚é‚½‚ß
	{
		return ((int)x == (int)other.x && (int)y == (int)other.y && (int)z == (int)other.z);
	}

	bool operator !=(const Vec3& other) //“ñ‚Â‚ÌƒxƒNƒgƒ‹‚ª“¯‚¶‚¶‚á‚È‚¢‚©‚Ç‚¤‚©‚ð”»•Ê‚·‚é‚½‚ß
	{
		return ((int)x != (int)other.x || (int)y != (int)other.y || (int)z != (int)other.z);
	}

	bool operator >=(const Vec3& other) //¶‚ª‰E‚æ‚è‘å‚«‚¢‚©“¯‚¶‚©‚Ç‚¤‚©‚ð”»•Ê‚·‚é‚½‚ß
	{
		return ((int)x >= (int)other.x && (int)y >= (int)other.y && (int)z >= (int)other.z);
	}

	bool operator <=(const Vec3& other) //¶‚ª‰E‚æ‚è¬‚³‚¢‚©“¯‚¶‚©‚Ç‚¤‚©‚ð”»•Ê‚·‚é‚½‚ß
	{
		return ((int)x <= (int)other.x && (int)y <= (int)other.y && (int)z <= (int)other.z);
	}

	bool operator <(const Vec3& other) //¶‚ª‰E‚æ‚è¬‚³‚¢‚©‚Ç‚¤‚©‚ð”»•Ê‚·‚é‚½‚ß
	{
		return ((int)x < (int)other.x || (int)y < (int)other.y || (int)z < (int)other.z);
	}

	bool operator >(const Vec3& other) //¶‚ª‰E‚æ‚è‘å‚«‚¢‚©‚Ç‚¤‚©‚ð”»•Ê‚·‚é‚½‚ß
	{
		return ((int)x > (int)other.x || (int)y > (int)other.y || (int)z > (int)other.z);
	}

	float LengthSq() const
	{
		return x * x + y * y + z * z;
	}

	float Length() const
	{
		return std::sqrt(LengthSq());
	}

	float dot(const Vec3& other)const
	{
		return x * other.x + y * other.y + z * other.z;
	}

	float distanceFrom(const Vec3& other)const
	{
		Vec3 v;
		v.x = x - other.x;
		v.y = y - other.y;
		v.z = z - other.z;

		return v.Length();
	}

	Vec3 Normalized()
	{
		return *this /= Length();
	}

	Vec3 Lerp(const Vec3& destination, float t)
	{
		x = x + (destination.x - x) * t;
		y = y + (destination.y - y) * t;
		z = z + (destination.z - z) * t;

		return *this;
	}

	float AngleForXZ()
	{
		float rad = (float)std::atan2((float)x, (float)z);
		float deg = rad * MyMath::Rad2Deg;

		return deg + 180.0f;
	}

	bool NotZero()
	{
		return *this != Vec3(0, 0, 0);
	}

	VECTOR Conv()
	{
		VECTOR a;
		a.x = x;
		a.y = y;
		a.z = z;
		return a;
	}

	Vec3 ConvBack(VECTOR other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
};


#endif // !VEC3_H_
