#include "GameObject.h"
#include <algorithm>
#include <string>

#include "../../Library/MyMath/MyMath.h"

void GameObject::update()
{
}

void GameObject::draw() const
{
}

void GameObject::draw_transparent() const
{
}

void GameObject::draw_gui() const
{
}

void GameObject::react(std::shared_ptr<GameObject> other)
{
}

void GameObject::collide(std::shared_ptr<GameObject> other)
{
	if (enable_collider_ && other->enable_collider_) {
		if (is_collide(other)) {
			react(other);
			other->react(shared_from_this());
		}
	}

}

void GameObject::die()
{
	dead_ = true;
}

bool GameObject::is_collide(const std::shared_ptr<GameObject> other)
{
	return collider().intersects(other->collider());
}

bool GameObject::is_dead() const
{
	return dead_;
}

const std::string& GameObject::name() const
{
	return name_;
}

const std::string& GameObject::tag() const
{
	return tag_;
}

const Transform& GameObject::transform() const
{
	return transform_;
}

Transform& GameObject::transform()
{
	return transform_;
}

Vec3 GameObject::velocity() const
{
	return velocity_;
}

SphereCollision GameObject::collider()
{
	return collider_.transform(transform_.position(), collider_.GetRadius());
}

float GameObject::height()
{
	float height = cube_collider_.GetScale().y;
	return height;
}

void GameObject::WallCollide()
{
	//壁の当たり判定があれば
	if (enable_wall_collider_ && gm.map_ != nullptr) {
		//オブジェクトの当たり判定位置更新
		cube_collider_.transform(transform_.position());
		//オブジェクトの位置を取得
		Vec3 pos = transform_.position();
		if (velocity_.z != 0) {
			//z軸移動中だったら、移動してない時の処理を減らすため
			transform_.position(cube_collider_.IsZWall(gm.map_, pos));
		}
		if (velocity_.x != 0) {
			//x軸移動中だったら、移動してない時の処理を減らすため
			transform_.position(cube_collider_.IsXWall(gm.map_, pos));
		}
	}
}

void GameObject::gravity()
{
	if (enable_gravity_) {
		if (transform_.position().y > 0) {
			gravity_velocity_.y += gravity_power_;
			//重力の大きさを制限
			gravity_velocity_.y = MyMath::clamp(gravity_velocity_.y, max_gravity_power_, 600.0f);
		}
		Vec3 position = transform_.position();
		position += gravity_velocity_;
		transform_.position(position);
		if (transform_.position().y < 0.0f) {
			//0以下にならないように
			gravity_velocity_.y = 0;
			Vec3 currentPos = transform_.position();
			currentPos.y = 0;
			transform_.position(currentPos);
		}
	}
}

void GameObject::projectile_gravity()
{
	//重力あるのみ実行
	if (enable_gravity_) {
		//重力二つあるためこちを代用
		velocity_.y -= gravity_power_;
		velocity_.y = MyMath::clamp(velocity_.y, max_gravity_power_, 600.0f);
	}
}

void GameObject::grounded()
{
	gravity_velocity_.y = 0;
}

void GameObject::Jump(float jumpPower)
{
	gravity_velocity_.y = jumpPower;

}

bool GameObject::isAir()
{
	return (gravity_velocity_.y != 0);
}

Vec3 GameObject::gravity_velo()
{
	return gravity_velocity_;
}

void GameObject::minus_gravity_velo()
{
	gravity_velocity_ *= -1;
}

bool GameObject::is_gravity()
{
	return enable_gravity_;
}

bool GameObject::is_wallcollide()
{
	return enable_wall_collider_;
}
