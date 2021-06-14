#include "IdleAnim.h"
#include "../../Player.h"
#include "../WalkAnim/WalkAnim.h"

IdleAnim* IdleAnim::Instance()
{
	static IdleAnim instance;
	return &instance;
}

void IdleAnim::start(Player* owner)
{
	//もし待機アニメーションじゃなければ、待機アニメーションにする
	if (owner->anim_state() != Idle) {
		owner->set_anim(Idle);
	}
}

void IdleAnim::update(Player* owner)
{
	//アニメーション再生
	owner->animclass()->playAnim(0.5f);
	//移動したらアニメーションを歩くアニメーションにする
	if (owner->velocity().NotZero()) {
		owner->get_anim_state_machine()->change_state(WalkAnim::Instance());
	}
}

void IdleAnim::end(Player* owner)
{
}
