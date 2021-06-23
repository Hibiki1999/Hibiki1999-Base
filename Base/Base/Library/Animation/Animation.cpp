#include "Animation.h"
#include <DxLib.h>
#include "../Transform/Transform.h"
#include "../Transform/Vec3/Vec3.h"
#include <string>
#include "../MyMath/MyMath.h"

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

Vec3 Animation::playMovingAnim(float playSpeed, Transform& trans, bool isLoop, std::string boneName)
{
	// �A�j���[�V�����ňړ������Ă���t���[���̔ԍ�����������
	bone_index_ = MV1SearchFrame(model_handle_, boneName.c_str());
	//�A�j���[�V�������X�V�O�̃{�[���ʒu���擾
	Vec3 prevPos = get_bone_positon();
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
	//�A�j���[�V�������X�V�������Ƃ̃{�[���̈ʒu���擾
	Vec3 nowPos = get_bone_positon();
	//���f���̌������擾
	float Angle = trans.rotation().yaw;
	//�{�[���̈ړ��ʂ��v�Z
	Vec3  a = (nowPos - prevPos);
	//���f���̈ʒu���擾
	Vec3 modelPos = trans.position();
	//�ړ��ʂ����f���̌����ɍ��킹��
	float SinParam = std::sin(-Angle * MyMath::Deg2Rad);
	float CosParam = std::cos(-Angle * MyMath::Deg2Rad);
	modelPos.x += a.x * CosParam - a.z * SinParam;
	modelPos.y += a.y;
	modelPos.z += a.x * SinParam + a.z * CosParam;

	return modelPos;
}

Vec3 Animation::get_bone_positon()
{
	VECTOR boneVEC = MV1GetAttachAnimFrameLocalPosition(model_handle_, anim_handle_, bone_index_);
	Vec3 prevPos;
	return prevPos.ConvBack(boneVEC);
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

bool Animation::playEnded()
{
	//�Đ��I���������ԋp
	return loop_end_notify_;
}

bool Animation::isAnimCurrentTime(float time)
{
	//time�͈͓̔���������
	return ((anim_play_time_ > time) && (anim_play_time_ < (time + 1.0f)));
}
