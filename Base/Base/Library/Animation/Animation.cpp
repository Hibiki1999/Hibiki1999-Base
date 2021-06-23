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

Vec3 Animation::playMovingAnim(float playSpeed, Transform& trans, bool isLoop, std::string boneName)
{
	// アニメーションで移動をしているフレームの番号を検索する
	bone_index_ = MV1SearchFrame(model_handle_, boneName.c_str());
	//アニメーションを更新前のボーン位置を取得
	Vec3 prevPos = get_bone_positon();
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
	//アニメーションを更新したあとのボーンの位置を取得
	Vec3 nowPos = get_bone_positon();
	//モデルの向きを取得
	float Angle = trans.rotation().yaw;
	//ボーンの移動量を計算
	Vec3  a = (nowPos - prevPos);
	//モデルの位置を取得
	Vec3 modelPos = trans.position();
	//移動量をモデルの向きに合わせる
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

bool Animation::playEnded()
{
	//再生終わったかを返却
	return loop_end_notify_;
}

bool Animation::isAnimCurrentTime(float time)
{
	//timeの範囲内だったら
	return ((anim_play_time_ > time) && (anim_play_time_ < (time + 1.0f)));
}
