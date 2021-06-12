#ifndef QUATERNION_H_
#define QUATERNION_H_

#include <cmath>

struct Quaternion
{
	float pitch = 0.0f;//pitch
	float yaw = 0.0f;//yaw
	float roll = 0.0f;//roll

	Quaternion() = default;

	Quaternion(float _pitch, float _yaw, float _roll);

	Quaternion operator +(const Quaternion& other) const; // 2項 +

	Quaternion operator -(const Quaternion& other) const; // 2項 -

	Quaternion operator *(float s) const; // 2項 *

	Quaternion operator /(float s) const; // 2項 /

	Quaternion& operator +=(const Quaternion& other); // 複合代入演算 +=

	Quaternion& operator -=(const Quaternion& other); // 複合代入演算 -=

	Quaternion& operator *=(float s); // 複合代入演算 *=

	Quaternion& operator /=(float s); // 複合代入演算 /=

	bool operator ==(const Quaternion& other); //二つのベクトルが同じかどうかを判別するため

	bool operator !=(const Quaternion& other); //二つのベクトルが同じじゃないかどうかを判別するため

	bool operator >=(const Quaternion& other); //左が右より大きいか同じかどうかを判別するため

	bool operator <=(const Quaternion& other); //左が右より小さいか同じかどうかを判別するため

	bool operator <(const Quaternion& other); //左が右より小さいかどうかを判別するため

	bool operator >(const Quaternion& other); //左が右より大きいかどうかを判別するため

	float LengthSq() const;

	float Length() const;

	float dot(const Quaternion& other)const;

	float distanceFrom(const Quaternion& other)const;

	Quaternion Normalized() const;

	Quaternion Lerp(const Quaternion& destination, float t);
};

#endif // !QUATERNION_H_
