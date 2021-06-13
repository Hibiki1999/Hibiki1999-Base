#include "Player.h"

Player::Player(const Vec3 position)
{
	this->name_ = "Player";
	this->tag_ = "PlayerTag";
	this->enable_wall_collider_ = true;
	transform_.position(position);
	transform_.rotation(Quaternion(0.0f, 180.0f, 0.0f));
	collider_ = SphereCollision(100.0f);
	cube_collider_ = CubeCollision(110.0f, 154.0f);
	anim.changeAnim(Anim::Idle);
}

void Player::update()
{
	AnimUpdate();
	InputHandle();

	std::string a= (isAir() ? "true" : "false");
	printfDx(a.c_str());
}

void Player::draw() const
{
	MyDraw::Draw3DModel(Image::ModelHandle, transform());
	collider_.draw(GetColor(0, 0, 255), GetColor(0, 0, 255));
	cube_collider_.draw();
	//printfDx(std::to_string(velocity_.y).c_str());
	//printfDx(std::to_string(transform_.position().y).c_str());
	printfDx("\n");
}

void Player::react(std::shared_ptr<GameObject> other)
{
	if (other->tag() == "EnemyTag") {
		//printfDx("YESS\n");
	}
}

void Player::AnimUpdate()
{
	if (animState == Anim::Idle) {
		anim.changeAnim(Anim::Idle);
		anim.playAnim(0.5f, true);
	}
	else if (animState == Anim::Walk) {
		anim.changeAnim(Anim::Walk);
		anim.playAnim(1.0f, true);
	}
}

void Player::InputHandle()
{
	Vec3 velocity{ 0.0f,0.0f,0.0f };
	if (Input::GetButton(Pad::All, "Forward")) {
		velocity.z = 10.0f;
		transform_.rotation(Quaternion(0.0f, 180.0f, 0.0f));
	}
	if (Input::GetButton(Pad::All, "Backward")) {
		velocity.z = -10.0f;
		transform_.rotation(Quaternion(0.0f, 0.0f, 0.0f));
	}
	if (Input::GetButton(Pad::All, "ToLeft")) {
		velocity.x = -10.0f;
		transform_.rotation(Quaternion(0.0f, 90.0f, 0.0f));
	}
	if (Input::GetButton(Pad::All, "ToRight")) {
		velocity.x = 10.0f;
		transform_.rotation(Quaternion(0.0f, 270.0f, 0.0f));
	}
	if (Input::GetButtonDown(Pad::All, "Jump")) {
		Jump(40.0f);
	}
	if (velocity != Vec3(0, 0, 0)) {
		animState = Anim::Walk;
	}
	else {
		animState = Anim::Idle;
	}

	if (velocity.NotZero()) {
		float angle = velocity.AngleForXZ();
		transform_.rotation(Quaternion(0, angle, 0));
	}

	velocity_ = velocity.Normalized() * 10.0f;
	

	Vec3 position = transform_.position();
	position += velocity_;
	transform_.position(position);
}

