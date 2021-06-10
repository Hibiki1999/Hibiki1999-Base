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

	Vec3 operator +(const Vec3& other) const // 2�� +
	{
		return{ x + other.x, y + other.y,z + other.z };
	}

	Vec3 operator -(const Vec3& other) const // 2�� -
	{
		return{ x - other.x, y - other.y,z - other.z };
	}

	Vec3 operator *(float s) const // 2�� *
	{
		return{ x * s, y * s,z * s };
	}

	Vec3 operator /(float s) const // 2�� /
	{
		return{ x / s, y / s ,z / s };
	}

	Vec3& operator +=(const Vec3& other) // ����������Z +=
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vec3& operator -=(const Vec3& other) // ����������Z -=
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vec3& operator *=(float s) // ����������Z *=
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	Vec3& operator /=(float s) // ����������Z /=
	{
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}

	bool operator ==(const Vec3& other) //��̃x�N�g�����������ǂ����𔻕ʂ��邽��
	{
		return ((int)x == (int)other.x && (int)y == (int)other.y && (int)z == (int)other.z);
	}

	bool operator !=(const Vec3& other) //��̃x�N�g������������Ȃ����ǂ����𔻕ʂ��邽��
	{
		return ((int)x != (int)other.x || (int)y != (int)other.y || (int)z != (int)other.z);
	}

	bool operator >=(const Vec3& other) //�����E���傫�����������ǂ����𔻕ʂ��邽��
	{
		return ((int)x >= (int)other.x && (int)y >= (int)other.y && (int)z >= (int)other.z);
	}

	bool operator <=(const Vec3& other) //�����E��菬�������������ǂ����𔻕ʂ��邽��
	{
		return ((int)x <= (int)other.x && (int)y <= (int)other.y && (int)z <= (int)other.z);
	}

	bool operator <(const Vec3& other) //�����E��菬�������ǂ����𔻕ʂ��邽��
	{
		return ((int)x < (int)other.x || (int)y < (int)other.y || (int)z < (int)other.z);
	}

	bool operator >(const Vec3& other) //�����E���傫�����ǂ����𔻕ʂ��邽��
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

	Vec3 Normalized() const
	{
		return { x / Length(), y / Length(), z / Length() };
	}

	Vec3 Lerp(const Vec3& destination, float t)
	{
		x = x + (destination.x - x) * t;
		y = y + (destination.y - y) * t;
		z = z + (destination.z - z) * t;

		return *this;
	}
};


#endif // !VEC3_H_