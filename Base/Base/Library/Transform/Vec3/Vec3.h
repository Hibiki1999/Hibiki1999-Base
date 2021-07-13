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

	Vec3 operator +(const Vec3& other) const // 2項 +
	{
		return{ x + other.x, y + other.y,z + other.z };
	}

	Vec3 operator -(const Vec3& other) const // 2項 -
	{
		return{ x - other.x, y - other.y,z - other.z };
	}

	Vec3 operator *(float s) const // 2項 *
	{
		return{ x * s, y * s,z * s };
	}

	Vec3 operator *(Vec3 s) const // 2項 *
	{
		return{ x * s.x, y * s.y,z * s.z };
	}

	Vec3 operator /(float s) const // 2項 /
	{
		return{ x / s, y / s ,z / s };
	}

	Vec3& operator +=(const Vec3& other) // 複合代入演算 +=
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vec3& operator -=(const Vec3& other) // 複合代入演算 -=
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vec3& operator *=(float s) // 複合代入演算 *=
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	Vec3& operator *=(Vec3 s) // 複合代入演算 *=
	{
		x *= s.x;
		y *= s.y;
		z *= s.z;
		return *this;
	}

	Vec3& operator /=(float s) // 複合代入演算 /=
	{
		if (s != 0)
		{
			this->x /= s;
			this->y /= s;
			this->z /= s;
		}
		return *this;
	}

	bool operator ==(const Vec3& other) //二つのベクトルが同じかどうかを判別するため
	{
		return ((int)x == (int)other.x && (int)y == (int)other.y && (int)z == (int)other.z);
	}

	bool operator !=(const Vec3& other) //二つのベクトルが同じじゃないかどうかを判別するため
	{
		return ((int)x != (int)other.x || (int)y != (int)other.y || (int)z != (int)other.z);
	}

	bool operator >=(const Vec3& other) //左が右より大きいか同じかどうかを判別するため
	{
		return ((int)x >= (int)other.x && (int)y >= (int)other.y && (int)z >= (int)other.z);
	}

	bool operator <=(const Vec3& other) //左が右より小さいか同じかどうかを判別するため
	{
		return ((int)x <= (int)other.x && (int)y <= (int)other.y && (int)z <= (int)other.z);
	}

	bool operator <(const Vec3& other) //左が右より小さいかどうかを判別するため
	{
		return ((int)x < (int)other.x || (int)y < (int)other.y || (int)z < (int)other.z);
	}

	bool operator >(const Vec3& other) //左が右より大きいかどうかを判別するため
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

#ifdef DX_LIB_H
	// Vector3からDxLibのVECTORへの変換
	VECTOR Vec3ToVec()
	{
		VECTOR Result;
		Result.x = this->x;
		Result.y = this->y;
		Result.z = this->z;
		return Result;
	}

	// 左辺値がDXのVECTOR型のときの=代入対応 VECTOR 左辺 = 右辺 Vector3 の場合の代入
	inline operator VECTOR() const //左辺値がDXのVECTOR型のときのみという縛りを加えるため constを付けた
	{
		VECTOR Result;
		Result.x = this->x;
		Result.y = this->y;
		Result.z = this->z;
		return Result;
	}

	// 右辺値がDXのVECTOR型のときの=代入対応 Vector3 左辺 = 右辺 VECTOR の場合の代入
	Vec3 operator=(const VECTOR& other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		return *this;
	}
#endif
};


#endif // !VEC3_H_
