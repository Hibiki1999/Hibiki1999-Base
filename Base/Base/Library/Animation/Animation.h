#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <string>

class Transform;
struct Vec3;

class Animation
{
public:
	Animation(int modelhandle);
	//�A�j���[�V�������Đ�
	void playAnim(float playSpeed, bool isLoop = true);
	//�ړ��ʂ���A�j���[�V�������Đ�
	Vec3 playMovingAnim(float playSpeed, Transform& trans, bool isLoop = false, std::string boneName = "Position");
	//�A�j���[�V������ς���
	void changeAnim(int animState);
	//�A�j���[�V�����Đ��I����(���[�v���Ȃ�����)
	bool playEnded();
	//����̎��Ԃ�
	bool isAnimCurrentTime(float time);


private:
	//���Đ����̃A�j���[�V�����ԍ�(�����A�j���[�V�����������ƍĐ������Ȃ��悤��)
	int prev_anim_state_ = -1;
	//�A�j���[�V�����ԍ�
	int anim_handle_ = 0;
	//�A�j���[�V�����f�[�^
	int prev_anim_handle_ = 0;
	//�A�j���[�V�����Đ����
	float anim_play_time_ = 0;
	//�A�j���[�V�����̒���
	float anim_total_time_ = 0;
	//�Đ��I���ʒm(���[�v���Ȃ�����)
	bool loop_end_notify_ = false;
	//�A�j���[�V�����̃��b�V��
	int model_handle_ = 0;
	//�ړ��A�j���\�V������Ή����邽�߃{�[�����擾
	int bone_index_ = -1;

	Vec3 get_bone_positon();
};

#endif // !ANIMATION_H_
