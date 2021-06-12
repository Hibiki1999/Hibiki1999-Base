#ifndef SPHERE_COLLISION_H_
#define SPHERE_COLLISION_H_

#include "../../Transform/Transform.h"

//境界球クラス
class SphereCollision
{
public:
	//コンストラクタ
	SphereCollision(float radius = 0.0f, const Vec3& position = Vec3{ 0.0f,0.0f,0.0f });
	//平行移動
	SphereCollision translate(const Vec3& position) const;
	//座標
	SphereCollision transform(const Vec3& position,float radius);
	//重なっているか？
	bool intersects(const SphereCollision& other) const;
	//デバッグ表示
	void draw() const;

	float GetRadius() const;

private:
	//半径
	float radius{ 0.0f };
	//中心座標

	Vec3 position{ 0.0f,0.0f,0.0f };
	Vec3 center{ 0.0f,0.0f,0.0f };

	bool SphereSphereCollision(const SphereCollision& other) const;
};

#endif // !SPHERE_COLLISION_H_
