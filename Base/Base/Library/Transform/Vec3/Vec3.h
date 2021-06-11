#ifndef VEC3_H_
#define VEC3_H_

#include <cmath>

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
		return sqrt(LengthSq());
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
		float deg = rad * (180.0f / 3.1415f);

		return deg + 180.0f;
	}

	bool NotZero()
	{
		return *this != Vec3(0, 0, 0);
	}
};


#endif // !VEC3_H_
