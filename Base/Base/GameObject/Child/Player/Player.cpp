#include "Player.h"

Player::Player(const Vec3 position)
{
	this->name_ = "Player";
	this->tag_ = "PlayerTag";
	transform_.position(position);
	collider_ = SphereCollision(5.0f);
	anim.changeAnim(Anim::Idle);
}

void Player::update()
{
	AnimUpdate();
	InputHandle();
}

void Player::draw() const
{
	MyDraw::Draw3DModel(Image::ModelHandle, transform());
	collider_.draw();
}

void Player::react(std::shared_ptr<GameObject> other)
{
	if (other->tag() == "EnemyTag") {
		printfDx("YESS\n");
	}
}

void Player::AnimUpdate()
{
	if (animState == Anim::Idle) {	
		anim.playAnim(0.5f, true);
	}
	else if (animState == Anim::Walk) {
		anim.playAnim(1.0f, false);
		if (anim.loopEnded()) {
			animState = Anim::Idle;
			anim.changeAnim(Anim::Idle);
		}
	}
	
	if (Input::GetButtonDown(Pad::All, PAD_INPUT_1)) {
		anim.changeAnim(Anim::Walk);
		animState = Anim::Walk;
	}
}

void Player::InputHandle()
{
	Vec3 velocity{ 0.0f,0.0f,0.0f };
	if (Input::GetButton(Pad::All, PAD_INPUT_UP))velocity.z = -10.0f;
	if (Input::GetButton(Pad::All, PAD_INPUT_DOWN))velocity.z = 10.0f;
	if (Input::GetButton(Pad::All, PAD_INPUT_LEFT))velocity.x = 10.0f;
	if (Input::GetButton(Pad::All, PAD_INPUT_RIGHT))velocity.x = -10.0f;
	
	Vec3 position = transform_.position();
	position += velocity;
	transform_.position(position);
}
