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

void GameObject::react(GameObject& other)
{
}

void GameObject::collide(GameObject& other)
{
	if (enable_collider_ && other.enable_collider_) {
		if (is_collide(other)) {
			react(other);
			other.react(*this);
		}
	}
}

void GameObject::die()
{
	dead_ = true;
}

bool GameObject::is_collide(const GameObject& other) const
{
	return collider().intersects(other.collider());
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

SphereCollision GameObject::collider() const
{
	return collider_.transform();

}