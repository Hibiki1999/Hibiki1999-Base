#ifndef SPHERE_COLLISION_H_
#define SPHERE_COLLISION_H_

#include "../../Transform/Transform.h"

//���E���N���X
class SphereCollision
{
public:
	//�R���X�g���N�^
	SphereCollision(float radius = 0.0f, const Vec3& position = Vec3{ 0.0f,0.0f,0.0f });
	//���s�ړ�
	SphereCollision translate(const Vec3& position) const;
	//���W
	SphereCollision transform(const Vec3& position,float radius);
	//�d�Ȃ��Ă��邩�H
	bool intersects(const SphereCollision& other) const;
	//�f�o�b�O�\��
	void draw() const;

	float GetRadius() const;

private:
	//���a
	float radius{ 0.0f };
	//���S���W

	Vec3 position{ 0.0f,0.0f,0.0f };
	Vec3 center{ 0.0f,0.0f,0.0f };

	bool SphereSphereCollision(const SphereCollision& other) const;
};

#endif // !SPHERE_COLLISION_H_
