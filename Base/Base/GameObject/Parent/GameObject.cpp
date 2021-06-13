#include "GameObject.h"

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

void GameObject::WallCollide()
{
	cube_collider_.transform(transform_.position());
	Vec3 pos = transform_.position();
	if (velocity_.z != 0) {
		transform_.position(cube_collider_.IsFrontWall(gm.map_, pos));
	}
	if (velocity_.x != 0) {
		transform_.position(cube_collider_.IsLeftWall(gm.map_, pos));
	}
	//transform_.position(cube_collider_.IsBackWall(gm.map_, pos));
	//transform_.position(cube_collider_.IsRightWall(gm.map_, pos));
}
