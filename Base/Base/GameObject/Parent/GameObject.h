#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string>

#include "../../Library/Mylib/MyMath.h"
#include "../../Library/Mylib/Screen.h"
#include "../../Library/Mylib/Input.h"
#include "../../Library/NotMyLib/GameManager.h"
#include"../../Resource/Image/Image.h"
#include "../../Library/MyLib/MyRandom.h"

class GameObject
{
public:

	std::string tag = "";

	float x = 0;
	float y = 0;
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

	// �����蔻��̍��[���擾
	virtual float GetLeft()
	{
		return (x - rotaGraphShiftX) + hitboxOffsetLeft;
	}

	// ���[���w�肷�邱�Ƃɂ��ʒu��ݒ肷��
	virtual void SetLeft(float left)
	{
		x = left - hitboxOffsetLeft + rotaGraphShiftX;
	}

	// �E�[���擾
	virtual float GetRight()
	{
		return (x - rotaGraphShiftX) + imageWidth - hitboxOffsetRight;
	}

	// �E�[���w�肷�邱�Ƃɂ��ʒu��ݒ肷��
	virtual void SetRight(float right)
	{
		x = right + hitboxOffsetRight - imageWidth + rotaGraphShiftX;
	}

	// ��[���擾
	virtual float GetTop()
	{
		return (y - rotaGraphShiftY) + hitboxOffsetTop;
	}

	// ��[���w�肷�邱�Ƃɂ��ʒu��ݒ肷��
	virtual void SetTop(float top)
	{
		y = top - hitboxOffsetTop + rotaGraphShiftY;
	}

	// ���[���擾����
	virtual float GetBottom()
	{
		return (y - rotaGraphShiftY) + imageHeight - hitboxOffsetBottom;
	}

	// ���[���w�肷�邱�Ƃɂ��ʒu��ݒ肷��
	virtual void SetBottom(float bottom)
	{
		y = bottom + hitboxOffsetBottom - imageHeight + rotaGraphShiftY;
	}

	// �_�ɏ��n�̂��߂�1�t���[���O�����֐��Q
	// 1�t���[���O����̈ړ��ʁix�����j
	virtual float GetDeltaX()
	{
		return x - prevX;
	}

	// 1�t���[���O����̈ړ��ʁiy�����j
	virtual float GetDeltaY()
	{
		return y - prevY;
	}

	// 1�t���[���O�̍��[���擾����
	virtual float GetPrevLeft()
	{
		return prevLeft;
	}

	// 1�t���[���O�̉E�[���擾����
	virtual float GetPrevRight()
	{
		return prevRight;
	}

	// 1�t���[���O�̏�[���擾����
	virtual float GetPrevTop()
	{
		return prevTop;
	}

	// 1�t���[���O�̉��[���擾����
	virtual float GetPrevBottom()
	{
		return prevBottom;
	}

	// 1�t���[���O�̏ꏊ�Ɠ����蔻����L������
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

