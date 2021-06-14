#ifndef ANIMATION_H_
#define ANIMATION_H_

class Animation
{
public:
	Animation(int modelhandle);
	//アニメーションを再生
	void playAnim(float playSpeed, bool isLoop = true);
	//アニメーションを変える
	void changeAnim(int animState);
	//アニメーション再生終了時(ループしない限定)
	bool loopEnded();
	//再生時間
	float animCurrentTime();
private:
	//今再生中のアニメーション番号(同じアニメーションをずっと再生させないように)
	int prev_anim_state_ = -1;
	//アニメーション番号
	int anim_handle_ = 0;
	//アニメーションデータ
	int prev_anim_handle_ = 0;
	//アニメーション再生状態
	float anim_play_time_ = 0;
	//アニメーションの長さ
	float anim_total_time_ = 0;
	//再生終了通知(ループしない限定)
	bool loop_end_notify_ = false;
	//アニメーションのメッシュ
	int model_handle_ = 0;

};

#endif // !ANIMATION_H_
