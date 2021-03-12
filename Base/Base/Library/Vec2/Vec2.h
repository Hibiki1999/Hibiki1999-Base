#ifndef VEC2_H_
#define VEC2_H_

#include <cmath>

struct Vec2
{
	float x;
	float y;

	Vec2() = default; // デフォルトコンストラクタ

	Vec2(float _x, float _y) : x(_x), y(_y) {}


	float length() const//ベクトルの長さを計算する
	{
		return sqrt(x * x + y * y);
	}

	float lengthSquare() const // ベクトルの長さの二乗
	{
		return x * x + y * y;
	}

	float dot(const Vec2& other) const // もう一方のベクトルとの内積
	{
		return x * other.x + y * other.y;
	}

	float distanceFrom(const Vec2& other) const    // もう一方のベクトルとの距離
	{
		return std::sqrt((other.x - x) * (other.x - x) + (other.y - y) * (other.y - y));
	}

	Vec2 operator +() const // 単項 +
	{
		return *this;
	}

	Vec2 operator -() const // 単項 -
	{
		return{ -x, -y };
	}

	Vec2 operator +(const Vec2& other) const // 2項 +
	{
		return{ x + other.x, y + other.y };
	}

	Vec2 operator -(const Vec2& other) const // 2項 -
	{
		return{ x - other.x, y - other.y };
	}

	Vec2 operator *(float s) const // 2項 *
	{
		return{ x * s, y * s };
	}

	Vec2 operator /(float s) const // 2項 /
	{
		return{ x / s, y / s };
	}

	Vec2& operator +=(const Vec2& other) // 複合代入演算 +=
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vec2& operator -=(const Vec2& other) // 複合代入演算 -=
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vec2& operator *=(float s) // 複合代入演算 *=
	{
		x *= s;
		y *= s;
		return *this;
	}

	Vec2& operator /=(float s) // 複合代入演算 /=
	{
		x /= s;
		y /= s;
		return *this;
	}

	bool operator ==(const Vec2& other) //二つのベクトルが同じかどうかを判別するため
	{
		return ((int)x == (int)other.x && (int)y == (int)other.y);
	}

	bool operator !=(const Vec2& other) //二つのベクトルが同じじゃないかどうかを判別するため
	{
		return ((int)x != (int)other.x || (int)y != (int)other.y);
	}

	bool operator >=(const Vec2& other) //左が右より大きいか同じかどうかを判別するため
	{
		return ((int)x >= (int)other.x && (int)y >= (int)other.y);
	}
	
	bool operator <=(const Vec2& other) //左が右より小さいか同じかどうかを判別するため
	{
		return ((int)x <= (int)other.x && (int)y <= (int)other.y);
	}
		
	bool operator <(const Vec2& other) //左が右より小さいかどうかを判別するため
	{
		return ((int)x < (int)other.x || (int)y < (int)other.y);
	}
		
	bool operator >(const Vec2& other) //左が右より大きいかどうかを判別するため
	{
		return ((int)x > (int)other.x || (int)y > (int)other.y);
	}

	Vec2 normalized() const // 正規化（長さを１にした）ベクトル
	{
		return{ x / length() , y / length() };
	}

	/// <summary>
	/// 両点の補間
	/// </summary>
	/// <param name="vec1">点1</param>
	/// <param name="vec2">点2</param>
	/// <param name="t"></param>
	/// <returns></returns>
	Vec2 lerp(const Vec2& vec1, const Vec2& vec2, float t) const
	{
		return Vec2(vec1.x + t * (vec2.x - vec1.x), vec1.y + t * (vec2.y - vec1.y));
	}
};

#endif // !VEC2_H_
