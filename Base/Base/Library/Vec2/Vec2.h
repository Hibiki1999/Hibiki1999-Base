#ifndef VEC2_H_
#define VEC2_H_

#include <cmath>

struct Vec2
{
	float x;
	float y;

	Vec2() = default; // �f�t�H���g�R���X�g���N�^

	Vec2(float _x, float _y) : x(_x), y(_y) {}


	float length() const//�x�N�g���̒������v�Z����
	{
		return sqrt(x * x + y * y);
	}

	float lengthSquare() const // �x�N�g���̒����̓��
	{
		return x * x + y * y;
	}

	float dot(const Vec2& other) const // ��������̃x�N�g���Ƃ̓���
	{
		return x * other.x + y * other.y;
	}

	float distanceFrom(const Vec2& other) const    // ��������̃x�N�g���Ƃ̋���
	{
		return std::sqrt((other.x - x) * (other.x - x) + (other.y - y) * (other.y - y));
	}

	Vec2 operator +() const // �P�� +
	{
		return *this;
	}

	Vec2 operator -() const // �P�� -
	{
		return{ -x, -y };
	}

	Vec2 operator +(const Vec2& other) const // 2�� +
	{
		return{ x + other.x, y + other.y };
	}

	Vec2 operator -(const Vec2& other) const // 2�� -
	{
		return{ x - other.x, y - other.y };
	}

	Vec2 operator *(float s) const // 2�� *
	{
		return{ x * s, y * s };
	}

	Vec2 operator /(float s) const // 2�� /
	{
		return{ x / s, y / s };
	}

	Vec2& operator +=(const Vec2& other) // ����������Z +=
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vec2& operator -=(const Vec2& other) // ����������Z -=
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vec2& operator *=(float s) // ����������Z *=
	{
		x *= s;
		y *= s;
		return *this;
	}

	Vec2& operator /=(float s) // ����������Z /=
	{
		x /= s;
		y /= s;
		return *this;
	}

	bool operator ==(const Vec2& other) //��̃x�N�g�����������ǂ����𔻕ʂ��邽��
	{
		return ((int)x == (int)other.x && (int)y == (int)other.y);
	}

	bool operator !=(const Vec2& other) //��̃x�N�g������������Ȃ����ǂ����𔻕ʂ��邽��
	{
		return ((int)x != (int)other.x || (int)y != (int)other.y);
	}

	bool operator >=(const Vec2& other) //�����E���傫�����������ǂ����𔻕ʂ��邽��
	{
		return ((int)x >= (int)other.x && (int)y >= (int)other.y);
	}
	
	bool operator <=(const Vec2& other) //�����E��菬�������������ǂ����𔻕ʂ��邽��
	{
		return ((int)x <= (int)other.x && (int)y <= (int)other.y);
	}
		
	bool operator <(const Vec2& other) //�����E��菬�������ǂ����𔻕ʂ��邽��
	{
		return ((int)x < (int)other.x || (int)y < (int)other.y);
	}
		
	bool operator >(const Vec2& other) //�����E���傫�����ǂ����𔻕ʂ��邽��
	{
		return ((int)x > (int)other.x || (int)y > (int)other.y);
	}

	Vec2 normalized() const // ���K���i�������P�ɂ����j�x�N�g��
	{
		return{ x / length() , y / length() };
	}

	/// <summary>
	/// ���_�̕��
	/// </summary>
	/// <param name="vec1">�_1</param>
	/// <param name="vec2">�_2</param>
	/// <param name="t"></param>
	/// <returns></returns>
	Vec2 lerp(const Vec2& vec1, const Vec2& vec2, float t) const
	{
		return Vec2(vec1.x + t * (vec2.x - vec1.x), vec1.y + t * (vec2.y - vec1.y));
	}
};

#endif // !VEC2_H_
