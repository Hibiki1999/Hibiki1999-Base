#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <string>

class Transform;
struct Vec3;

class Animation
{
public:
	Animation(int modelhandle);
	//アニメーションを再生
	void playAnim(float playSpeed, bool isLoop = true);
	//移動量あるアニメーションを再生
	Vec3 playMovingAnim(float playSpeed, Transform& trans, bool isLoop = false, std::string boneName = "Position");
	//アニメーションを変える
	void changeAnim(int animState);
	//アニメーション再生終了時(ループしない限定)
	bool playEnded();
	//特定の時間に
	bool isAnimCurrentTime(float time);


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
	//移動アニメ―ションを対応するためボーンを取得
	int bone_index_ = -1;

	Vec3 get_bone_positon();
};

#endif // !ANIMATION_H_
