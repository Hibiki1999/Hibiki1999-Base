#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "Vec3/Vec3.h"
#include "Vec2/Vec2.h"
#include "Quaternion/Quaternion.h"
#include "../MyMath/MyMath.h"

class Transform
{
public:

	Transform() = default;

	~Transform() {}

	Vec3 position() const
	{
		return position_;
	}

	void position(const Vec3& position)
	{
		position_ = position;
	}

	Quaternion rotation() const
	{
		return rotation_;
	}

	void rotation(const Quaternion& rotation)
	{
		rotation_ = rotation;
	}

	Vec3 scale()
	{
		return scale_;
	}

	void scale(const Vec3& scale)
	{
		scale_ = scale;
	}

	Vec3 front(Quaternion quart, float dis = 1.0f)
	{
		quart.yaw += 180;
		Vec2 a = Vec2(
			std::sin(quart.yaw * MyMath::Deg2Rad), std::cos(quart.yaw * MyMath::Deg2Rad));
		Vec3 b;
		b.x = a.x;
		b.y = 0.0f;
		b.z = a.y;

		b *= dis;
		b += position_;
		return b;
	}

	Vec3 left(Quaternion quart, float dis = 1.0f)
	{
		quart.yaw += 90;
		Vec2 a = Vec2(
			std::sin(quart.yaw * MyMath::Deg2Rad), std::cos(quart.yaw * MyMath::Deg2Rad));
		Vec3 b;
		b.x = a.x;
		b.y = 0.0f;
		b.z = a.y;

		b *= dis;
		b += position_;
		return b;
	}

	Vec3 right(Quaternion quart, float dis = 1.0f)
	{
		quart.yaw += 270;
		Vec2 a = Vec2(
			std::sin(quart.yaw * MyMath::Deg2Rad), std::cos(quart.yaw * MyMath::Deg2Rad));
		Vec3 b;
		b.x = a.x;
		b.y = 0.0f;
		b.z = a.y;

		b *= dis;
		b += position_;
		return b;
	}

	Vec3 back(Quaternion quart, float dis = 1.0f)
	{
		Vec2 a = Vec2(
			std::sin(quart.yaw * MyMath::Deg2Rad), std::cos(quart.yaw * MyMath::Deg2Rad));
		Vec3 b;
		b.x = a.x;
		b.y = 0.0f;
		b.z = a.y;

		b *= dis;
		b += position_;
		return b;
	}

private:
	// ポジション 
	Vec3 position_{ 0.0f, 0.0f, 0.0f };
	// 回転 
	Quaternion rotation_{ 0.0f, 0.0f, 0.0f };
	// スケール 
	Vec3 scale_{ 1.0f, 1.0f, 1.0f };

	// このトランスフォームの持ち主
	void* owner_{ nullptr };
};



#endif // !TRANSFORM_H_
