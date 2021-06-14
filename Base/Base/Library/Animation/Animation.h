#ifndef ANIMATION_H_
#define ANIMATION_H_

class Animation
{
public:
	Animation(int modelhandle);
	//�A�j���[�V�������Đ�
	void playAnim(float playSpeed, bool isLoop = true);
	//�A�j���[�V������ς���
	void changeAnim(int animState);
	//�A�j���[�V�����Đ��I����(���[�v���Ȃ�����)
	bool loopEnded();
	//�Đ�����
	float animCurrentTime();
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

};

#endif // !ANIMATION_H_
