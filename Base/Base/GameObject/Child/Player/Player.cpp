#include "Player.h"
#include "AnimStateMachine/IdleAnim/IdleAnim.h"
#include "AnimStateMachine/WalkAnim/WalkAnim.h"
#include "../../../Library/StateMachine/State.h"
#include "../../../Resource/Effect/Child/Explo/Explo.h"

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
	anim_state_machine_ = new StateMachine<Player>(this);
	anim_state_machine_->set_current_state(IdleAnim::Instance());
}

void Player::update()
{
	InputHandle();
	anim_state_machine_->update();
	//if (Input::GetButtonDown(Pad::All, PAD_INPUT_1))gm.effects.push_back(std::make_shared<Explo>(transform_.position()));
}

void Player::draw() const
{
	MyDraw::Draw3DModel(Image::ModelHandle, transform());
	//MyDraw::DrawPlaneCharaRotaGraphF3D(transform_.position(), 1, 0, Image::Boss, 1);
	//collider_.draw(GetColor(0, 0, 255), GetColor(0, 0, 255));
	//cube_collider_.draw();
}

void Player::react(std::shared_ptr<GameObject> other)
{
	if (other->tag() == "EnemyTag") {
		//printfDx("YESS\n");
	}
}

int Player::anim_state()
{
	return anim_state_;
}

void Player::set_anim(int anim)
{
	this->anim.changeAnim(anim);
	anim_state_ = anim;
}

StateMachine<Player>* Player::get_anim_state_machine() const
{
	return anim_state_machine_;
}

Animation* Player::animclass()
{
	return &anim;
}

void Player::InputHandle()
{
	//Vec3 velocity{ 0.0f,0.0f,0.0f };
	//if (Input::GetButton(Pad::All, "Forward")) {
	//	velocity.z = 10.0f;
	//	transform_.rotation(Quaternion(0.0f, 180.0f, 0.0f));
	//}
	//if (Input::GetButton(Pad::All, "Backward")) {
	//	velocity.z = -10.0f;
	//	transform_.rotation(Quaternion(0.0f, 0.0f, 0.0f));
	//}
	//if (Input::GetButton(Pad::All, "ToLeft")) {
	//	velocity.x = -10.0f;
	//	transform_.rotation(Quaternion(0.0f, 90.0f, 0.0f));
	//}
	//if (Input::GetButton(Pad::All, "ToRight")) {
	//	velocity.x = 10.0f;
	//	transform_.rotation(Quaternion(0.0f, 270.0f, 0.0f));
	//}
	//if (Input::GetButtonDown(Pad::All, "Jump")) {
	//	Jump(40.0f);
	//}

	//if (velocity.NotZero()) {
	//	float angle = velocity.AngleForXZ();
	//	transform_.rotation(Quaternion(0, angle, 0));
	//}

	//velocity_ = velocity.Normalized() * 10.0f;

	//Vec3 position = transform_.position();
	//position += velocity_;
	//transform_.position(position);
}

