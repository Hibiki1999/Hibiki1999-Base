#ifndef QUATERNION_H_
#define QUATERNION_H_

#include <cmath>

struct Quaternion
{
	float pitch = 0.0f;//pitch
	float yaw = 0.0f;//yaw
	float roll = 0.0f;//roll

	Quaternion() = default;

	Quaternion(float _pitch, float _yaw, float _roll) :pitch(_pitch), yaw(_yaw), roll(_roll) {}

	Quaternion operator +(const Quaternion& other) const // 2�� +
	{
		return{ pitch + other.pitch, yaw + other.yaw,roll + other.roll };
	}

	Quaternion operator -(const Quaternion& other) const // 2�� -
	{
		return{ pitch - other.pitch, yaw - other.yaw,roll - other.roll };
	}

	Quaternion operator *(float s) const // 2�� *
	{
		return{ pitch * s, yaw * s,roll * s };
	}

	Quaternion operator /(float s) const // 2�� /
	{
		return{ pitch / s, yaw / s ,roll / s };
	}

	Quaternion& operator +=(const Quaternion& other) // ����������Z +=
	{
		pitch += other.pitch;
		yaw += other.yaw;
		roll += other.roll;
		return *this;
	}

	Quaternion& operator -=(const Quaternion& other) // ����������Z -=
	{
		pitch -= other.pitch;
		yaw -= other.yaw;
		roll -= other.roll;
		return *this;
	}

	Quaternion& operator *=(float s) // ����������Z *=
	{
		pitch *= s;
		yaw *= s;
		roll *= s;
		return *this;
	}

	Quaternion& operator /=(float s) // ����������Z /=
	{
		pitch /= s;
		yaw /= s;
		roll /= s;
		return *this;
	}

	bool operator ==(const Quaternion& other) //��̃x�N�g�����������ǂ����𔻕ʂ��邽��
	{
		return ((int)pitch == (int)other.pitch && (int)yaw == (int)other.yaw && (int)roll == (int)other.roll);
	}

	bool operator !=(const Quaternion& other) //��̃x�N�g������������Ȃ����ǂ����𔻕ʂ��邽��
	{
		return ((int)pitch != (int)other.pitch || (int)yaw != (int)other.yaw || (int)roll != (int)other.roll);
	}

	bool operator >=(const Quaternion& other) //�����E���傫�����������ǂ����𔻕ʂ��邽��
	{
		return ((int)pitch >= (int)other.pitch && (int)yaw >= (int)other.yaw && (int)roll >= (int)other.roll);
	}

	bool operator <=(const Quaternion& other) //�����E��菬�������������ǂ����𔻕ʂ��邽��
	{
		return ((int)pitch <= (int)other.pitch && (int)yaw <= (int)other.yaw && (int)roll <= (int)other.roll);
	}

	bool operator <(const Quaternion& other) //�����E��菬�������ǂ����𔻕ʂ��邽��
	{
		return ((int)pitch < (int)other.pitch || (int)yaw < (int)other.yaw || (int)roll < (int)other.roll);
	}

	bool operator >(const Quaternion& other) //�����E���傫�����ǂ����𔻕ʂ��邽��
	{
		return ((int)pitch > (int)other.pitch || (int)yaw > (int)other.yaw || (int)roll > (int)other.roll);
	}

	float LengthSq() const
	{
		return pitch * pitch + yaw * yaw + roll * roll;
	}

	float Length() const
	{
		return sqrt(LengthSq());
	}

	float dot(const Quaternion& other)const
	{
		return pitch * other.pitch + yaw * other.yaw + roll * other.roll;
	}

	float distanceFrom(const Quaternion& other)const
	{
		Quaternion v;
		v.pitch = pitch - other.pitch;
		v.yaw = yaw - other.yaw;
		v.roll = roll - other.roll;

		return v.Length();
	}

	Quaternion Normalized() const
	{
		return { pitch / Length(), yaw / Length(), roll / Length() };
	}

	Quaternion Lerp(const Quaternion& destination, float t)
	{
		pitch = pitch + (destination.pitch - pitch) * t;
		yaw = yaw + (destination.yaw - yaw) * t;
		roll = roll + (destination.roll - roll) * t;

		return *this;
	}
};

#endif // !QUATERNION_H_
