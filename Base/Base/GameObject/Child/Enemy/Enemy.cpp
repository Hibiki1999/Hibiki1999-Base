#include "Enemy.h"
#include "../../../Library/MyDraw/MyDraw.h"
Enemy::Enemy(const Vec3 position)
{
	this->name_ = "Enemy";
	this->tag_ = "EnemyTag";
	transform_.position(position);
	collider_ = SphereCollision(5.0f);
}

void Enemy::update()
{
}

void Enemy::draw() const
{
	//MyDraw::Draw3DModel(Image::sword, transform_);
	collider_.draw();
}

void Enemy::react(std::shared_ptr<GameObject> other)
{
	if (other->tag() == "PlayerTag") {
		
	}
}
