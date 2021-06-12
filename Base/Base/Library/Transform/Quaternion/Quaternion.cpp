#include "Quaternion.h"

inline Quaternion::Quaternion(float _pitch, float _yaw, float _roll) :pitch(_pitch), yaw(_yaw), roll(_roll) {}

Quaternion Quaternion::operator+(const Quaternion& other) const
{
	return{ pitch + other.pitch, yaw + other.yaw,roll + other.roll };
}

Quaternion Quaternion::operator-(const Quaternion& other) const
{
	return{ pitch - other.pitch, yaw - other.yaw,roll - other.roll };
}

Quaternion Quaternion::operator*(float s) const
{
	return{ pitch * s, yaw * s,roll * s };
}

Quaternion Quaternion::operator/(float s) const
{
	return{ pitch / s, yaw / s ,roll / s };
}

Quaternion& Quaternion::operator+=(const Quaternion& other)
{
	pitch += other.pitch;
	yaw += other.yaw;
	roll += other.roll;
	return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& other)
{
	pitch -= other.pitch;
	yaw -= other.yaw;
	roll -= other.roll;
	return *this;
}

Quaternion& Quaternion::operator*=(float s)
{
	pitch *= s;
	yaw *= s;
	roll *= s;
	return *this;
}

Quaternion& Quaternion::operator/=(float s)
{
	pitch /= s;
	yaw /= s;
	roll /= s;
	return *this;
}

bool Quaternion::operator==(const Quaternion& other)
{
	return ((int)pitch == (int)other.pitch && (int)yaw == (int)other.yaw && (int)roll == (int)other.roll);
}

bool Quaternion::operator!=(const Quaternion& other)
{
	return ((int)pitch != (int)other.pitch || (int)yaw != (int)other.yaw || (int)roll != (int)other.roll);
}

bool Quaternion::operator>=(const Quaternion& other)
{
	return ((int)pitch >= (int)other.pitch && (int)yaw >= (int)other.yaw && (int)roll >= (int)other.roll);
}

bool Quaternion::operator<=(const Quaternion& other)
{
	return ((int)pitch <= (int)other.pitch && (int)yaw <= (int)other.yaw && (int)roll <= (int)other.roll);
}

bool Quaternion::operator<(const Quaternion& other)
{
	return ((int)pitch < (int)other.pitch || (int)yaw < (int)other.yaw || (int)roll < (int)other.roll);
}

bool Quaternion::operator>(const Quaternion& other)
{
	return ((int)pitch > (int)other.pitch || (int)yaw > (int)other.yaw || (int)roll > (int)other.roll);
}

inline float Quaternion::LengthSq() const
{
	return pitch * pitch + yaw * yaw + roll * roll;
}

inline float Quaternion::Length() const
{
	return sqrt(LengthSq());
}

inline float Quaternion::dot(const Quaternion& other) const
{
	return pitch * other.pitch + yaw * other.yaw + roll * other.roll;
}

inline float Quaternion::distanceFrom(const Quaternion& other) const
{
	Quaternion v;
	v.pitch = pitch - other.pitch;
	v.yaw = yaw - other.yaw;
	v.roll = roll - other.roll;

	return v.Length();
}

inline Quaternion Quaternion::Normalized() const
{
	return { pitch / Length(), yaw / Length(), roll / Length() };
}

inline Quaternion Quaternion::Lerp(const Quaternion& destination, float t)
{
	pitch = pitch + (destination.pitch - pitch) * t;
	yaw = yaw + (destination.yaw - yaw) * t;
	roll = roll + (destination.roll - roll) * t;

	return *this;
}
