#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string>

#include "../../Library/MyMath/MyMath.h"
#include "../../Library/Screen/Screen.h"
#include "../../Library/Input/Input.h"
#include "../../Library/GameManager/GameManager.h"
#include"../../Resource/Image/Image.h"
#include "../../Library/MyRandom/MyRandom.h"

class GameObject
{
public:

	std::string tag = "";

	float x = 0;
	float y = 0;

	float moveSpeed = 0;
	float vx = 0;
	float vy = 0;

	bool isDead = false;

	int imageWidth = 0;
	int imageHeight = 0;
	int hitboxOffsetLeft = 0;
	int hitboxOffsetRight = 0;
	int hitboxOffsetTop = 0;
	int hitboxOffsetBottom = 0;

	float rotaGraphShiftX = 0;
	float rotaGraphShiftY = 0;

	float prevX = 0;
	float prevY = 0;

	float prevLeft = 0;
	float prevRight = 0;
	float prevTop = 0;
	float prevBottom = 0;

	GameObject()
	{
	}

	virtual ~GameObject()
	{
	}

	// 当たり判定の左端を取得
	virtual float GetLeft()
	{
		return (x - rotaGraphShiftX) + hitboxOffsetLeft;
	}

	// 左端を指定することにより位置を設定する
	virtual void SetLeft(float left)
	{
		x = (left - hitboxOffsetLeft + rotaGraphShiftX) - 1;
	}

	// 右端を取得
	virtual float GetRight()
	{
		return (x - rotaGraphShiftX) + imageWidth - hitboxOffsetRight;
	}

	// 右端を指定することにより位置を設定する
	virtual void SetRight(float right)
	{
		x = (right + hitboxOffsetRight - imageWidth + rotaGraphShiftX) + 1;
	}

	// 上端を取得
	virtual float GetTop()
	{
		return y - rotaGraphShiftY + hitboxOffsetTop;
	}

	// 上端を指定することにより位置を設定する
	virtual void SetTop(float top)
	{
		y = (top + hitboxOffsetTop + rotaGraphShiftY) + 1;
	}

	// 下端を取得する
	virtual float GetBottom()
	{
		return (y - rotaGraphShiftY) + imageHeight - hitboxOffsetBottom;
	}

	// 下端を指定することにより位置を設定する
	virtual void SetBottom(float bottom)
	{
		y = (bottom + hitboxOffsetBottom - imageHeight + rotaGraphShiftY) - 1;
	}

	// 雲に乗る系のための1フレーム前処理関数群
	// 1フレーム前からの移動量（x方向）
	virtual float GetDeltaX()
	{
		return x - prevX;
	}

	// 1フレーム前からの移動量（y方向）
	virtual float GetDeltaY()
	{
		return y - prevY;
	}

	// 1フレーム前の左端を取得する
	virtual float GetPrevLeft()
	{
		return prevLeft;
	}

	// 1フレーム前の右端を取得する
	virtual float GetPrevRight()
	{
		return prevRight;
	}

	// 1フレーム前の上端を取得する
	virtual float GetPrevTop()
	{
		return prevTop;
	}

	// 1フレーム前の下端を取得する
	virtual float GetPrevBottom()
	{
		return prevBottom;
	}

	// 1フレーム前の場所と当たり判定を記憶する
	virtual void StorePostionAndHitBox()
	{
		prevX = x;
		prevY = y;
		prevLeft = GetLeft();
		prevRight = GetRight();
		prevTop = GetTop();
		prevBottom = GetBottom();
	}

	virtual void Update() = 0;

	virtual void Draw() = 0;
};

#endif // !GAMEOBJECT_H_

