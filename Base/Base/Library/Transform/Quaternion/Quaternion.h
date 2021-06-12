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

	Quaternion operator +(const Quaternion& other) const; // 2�� +

	Quaternion operator -(const Quaternion& other) const; // 2�� -

	Quaternion operator *(float s) const; // 2�� *

	Quaternion operator /(float s) const; // 2�� /

	Quaternion& operator +=(const Quaternion& other); // ����������Z +=

	Quaternion& operator -=(const Quaternion& other); // ����������Z -=

	Quaternion& operator *=(float s); // ����������Z *=

	Quaternion& operator /=(float s); // ����������Z /=

	bool operator ==(const Quaternion& other); //��̃x�N�g�����������ǂ����𔻕ʂ��邽��

	bool operator !=(const Quaternion& other); //��̃x�N�g������������Ȃ����ǂ����𔻕ʂ��邽��

	bool operator >=(const Quaternion& other); //�����E���傫�����������ǂ����𔻕ʂ��邽��

	bool operator <=(const Quaternion& other); //�����E��菬�������������ǂ����𔻕ʂ��邽��

	bool operator <(const Quaternion& other); //�����E��菬�������ǂ����𔻕ʂ��邽��

	bool operator >(const Quaternion& other); //�����E���傫�����ǂ����𔻕ʂ��邽��

	float LengthSq() const;

	float Length() const;

	float dot(const Quaternion& other)const;

	float distanceFrom(const Quaternion& other)const;

	Quaternion Normalized() const;

	Quaternion Lerp(const Quaternion& destination, float t);
};

#endif // !QUATERNION_H_
