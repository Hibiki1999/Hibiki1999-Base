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
	//�����ҋ@�A�j���[�V��������Ȃ���΁A�ҋ@�A�j���[�V�����ɂ���
	if (owner->anim_state() != Idle) {
		owner->set_anim(Idle);
	}
}

void IdleAnim::update(Player* owner)
{
	//�A�j���[�V�����Đ�
	owner->animclass()->playAnim(0.5f);
	//�ړ�������A�j���[�V����������A�j���[�V�����ɂ���
	if (owner->velocity().NotZero()) {
		owner->get_anim_state_machine()->change_state(WalkAnim::Instance());
	}
}

void IdleAnim::end(Player* owner)
{
}
