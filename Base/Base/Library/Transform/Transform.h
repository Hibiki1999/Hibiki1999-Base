#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "Vec3/Vec3.h"
#include "Quaternion/Quaternion.h"

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

private:
	// �|�W�V���� 
	Vec3 position_{ 0.0f, 0.0f, 0.0f };
	// ��] 
	Quaternion rotation_{ 0.0f, 0.0f, 0.0f };
	// �X�P�[�� 
	Vec3 scale_{ 1.0f, 1.0f, 1.0f };

	// ���̃g�����X�t�H�[���̎�����
	void* owner_{ nullptr };
};



#endif // !TRANSFORM_H_
