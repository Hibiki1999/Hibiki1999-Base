#include "Animation.h"
#include <DxLib.h>

Animation::Animation(int modelhandle)
{
	this->model_handle_ = modelhandle;
}

void Animation::playAnim(float playSpeed, bool isLoop)
{
	//アニメーションを再生するために時間を流す
	anim_play_time_ += playSpeed;
	//ループかつアニメーションを再生完了する時に、アニメーションをもう一度最初から再生する
	if ((anim_play_time_ >= anim_total_time_) && isLoop) {
		anim_play_time_ = 0.0f;
	}
	else if ((anim_play_time_ >= anim_total_time_) && !isLoop) {
		loop_end_notify_ = true;
	}
	//アニメーションの再生
	MV1SetAttachAnimTime(model_handle_, anim_handle_, anim_play_time_);
}

void Animation::changeAnim(int animState)
{
	//アニメーションのループ完了通知をoff
	loop_end_notify_ = false;
	//前回と違うアニメーションが呼ばれたら
	if (prev_anim_state_ != animState) {
		//新しいアニメーションを登録
		prev_anim_state_ = animState;
		//以前のアニメ―ションをデタッチ
		MV1DetachAnim(model_handle_, prev_anim_handle_);
		//以前のアニメーションを次回のデタッチするため一旦保存
		prev_anim_handle_ = anim_handle_;

		//新しいアニメーションを登録
		anim_handle_ = MV1AttachAnim(model_handle_, animState);
		//新しいアニメーションの長さを調べる
		anim_total_time_ = MV1GetAttachAnimTotalTime(model_handle_, anim_handle_);
		//アニメーションの再生時間を0にする(0にしないと途中から再生される可能性はある)
		anim_play_time_ = 0;
		MV1SetAttachAnimTime(model_handle_, anim_handle_, 0);
	}
}

bool Animation::loopEnded()
{
	//再生終わったかを返却
	return loop_end_notify_;
}
