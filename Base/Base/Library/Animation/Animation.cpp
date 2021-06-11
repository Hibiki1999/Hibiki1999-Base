#include "Animation.h"
#include <DxLib.h>

Animation::Animation(int modelhandle)
{
	this->model_handle_ = modelhandle;
}

void Animation::playAnim(float playSpeed, bool isLoop)
{
	//�A�j���[�V�������Đ����邽�߂Ɏ��Ԃ𗬂�
	anim_play_time_ += playSpeed;
	//���[�v���A�j���[�V�������Đ��������鎞�ɁA�A�j���[�V������������x�ŏ�����Đ�����
	if ((anim_play_time_ >= anim_total_time_) && isLoop) {
		anim_play_time_ = 0.0f;
	}
	else if ((anim_play_time_ >= anim_total_time_) && !isLoop) {
		loop_end_notify_ = true;
	}
	//�A�j���[�V�����̍Đ�
	MV1SetAttachAnimTime(model_handle_, anim_handle_, anim_play_time_);
}

void Animation::changeAnim(int animState)
{
	//�A�j���[�V�����̃��[�v�����ʒm��off
	loop_end_notify_ = false;
	//�O��ƈႤ�A�j���[�V�������Ă΂ꂽ��
	if (prev_anim_state_ != animState) {
		//�V�����A�j���[�V������o�^
		prev_anim_state_ = animState;
		//�ȑO�̃A�j���\�V�������f�^�b�`
		MV1DetachAnim(model_handle_, prev_anim_handle_);
		//�ȑO�̃A�j���[�V����������̃f�^�b�`���邽�߈�U�ۑ�
		prev_anim_handle_ = anim_handle_;

		//�V�����A�j���[�V������o�^
		anim_handle_ = MV1AttachAnim(model_handle_, animState);
		//�V�����A�j���[�V�����̒����𒲂ׂ�
		anim_total_time_ = MV1GetAttachAnimTotalTime(model_handle_, anim_handle_);
		//�A�j���[�V�����̍Đ����Ԃ�0�ɂ���(0�ɂ��Ȃ��Ɠr������Đ������\���͂���)
		anim_play_time_ = 0;
		MV1SetAttachAnimTime(model_handle_, anim_handle_, 0);
	}
}

bool Animation::loopEnded()
{
	//�Đ��I���������ԋp
	return loop_end_notify_;
}
