#include "WalkAnim.h"
#include "../../Player.h"
#include "../IdleAnim/IdleAnim.h"

WalkAnim* WalkAnim::Instance()
{
	static WalkAnim instance;
	return &instance;
}

void WalkAnim::start(Player* owner)
{
	//もし歩いてるアニメーションじゃなければ、歩くアニメーションに変える
	if (owner->anim_state() != Walk) {
		owner->set_anim(Walk);		
	}
}

void WalkAnim::update(Player* owner)
{
	//アニメーション再生
	owner->animclass()->playAnim(0.7f);
	//停止したらアニメーションを待機アニメーションに変える
	if (owner->velocity() == Vec3(0, 0, 0)) {
		owner->get_anim_state_machine()->change_state(IdleAnim::Instance());
	}
}

void WalkAnim::end(Player* owner)
{
}
