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

void GameObject::WallCollide()
{
	//�ǂ̓����蔻�肪�����
	if (enable_wall_collider_) {
		//�I�u�W�F�N�g�̓����蔻��ʒu�X�V
		cube_collider_.transform(transform_.position());
		//�I�u�W�F�N�g�̈ʒu���擾
		Vec3 pos = transform_.position();
		if (velocity_.z != 0) {
			//z���ړ�����������A�ړ����ĂȂ����̏��������炷����
			transform_.position(cube_collider_.IsZWall(gm.map_, pos));
		}
		if (velocity_.x != 0) {
			//x���ړ�����������A�ړ����ĂȂ����̏��������炷����
			transform_.position(cube_collider_.IsXWall(gm.map_, pos));
		}
	}
}

void GameObject::gravity()
{
	if (enable_gravity_) {
		if (transform_.position().y > 0) {
			gravity_velocity.y += gravity_power_;
			//�d�͂̑傫���𐧌�
			gravity_velocity.y = MyMath::clamp(gravity_velocity.y, max_gravity_power_, 600.0f);
		}
		Vec3 position = transform_.position();
		position += gravity_velocity;
		transform_.position(position);
		if (transform_.position().y < 0.0f) {
			//0�ȉ��ɂȂ�Ȃ��悤��
			gravity_velocity.y = 0;
			Vec3 currentPos = transform_.position();
			currentPos.y = 0;
			transform_.position(currentPos);
		}
	}
}

void GameObject::projectile_gravity()
{
	//�d�͂���̂ݎ��s
	if (enable_gravity_) {
		//�d�͓���邽�߂������p
		velocity_.y -= gravity_power_;
		velocity_.y = MyMath::clamp(velocity_.y, max_gravity_power_, 600.0f);
	}
}

void GameObject::Jump(float jumpPower)
{
	gravity_velocity.y = jumpPower;

}

bool GameObject::isAir()
{
	return (gravity_velocity.y != 0);
}
