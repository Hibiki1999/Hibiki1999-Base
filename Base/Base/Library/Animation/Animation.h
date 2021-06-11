#ifndef ANIMATION_H_
#define ANIMATION_H_

class Animation
{
public:
	Animation(int modelhandle);

	void playAnim(float playSpeed,bool isLoop);

	void changeAnim(int animState);

	bool loopEnded();

	float animCurrentTime();
private:

	int prev_anim_state_ = -1;
	int anim_handle_ = 0;
	int prev_anim_handle_ = 0;
	float anim_play_time_ = 0;
	float anim_total_time_ = 0;
	bool loop_end_notify_ = false;

	int model_handle_ = 0;

};

#endif // !ANIMATION_H_
