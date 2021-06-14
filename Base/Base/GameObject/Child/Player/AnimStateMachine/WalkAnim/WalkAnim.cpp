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
	//���������Ă�A�j���[�V��������Ȃ���΁A�����A�j���[�V�����ɕς���
	if (owner->anim_state() != Walk) {
		owner->set_anim(Walk);		
	}
}

void WalkAnim::update(Player* owner)
{
	//�A�j���[�V�����Đ�
	owner->animclass()->playAnim(0.7f);
	//��~������A�j���[�V������ҋ@�A�j���[�V�����ɕς���
	if (owner->velocity() == Vec3(0, 0, 0)) {
		owner->get_anim_state_machine()->change_state(IdleAnim::Instance());
	}
}

void WalkAnim::end(Player* owner)
{
}
