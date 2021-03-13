#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string>

#include "../../Library/MyMath/MyMath.h"
#include "../../Library/Screen/Screen.h"
#include "../../Library/Input/Input.h"
#include "../../Library/GameManager/GameManager.h"
#include"../../Resource/Image/Image.h"
#include "../../Library/MyRandom/MyRandom.h"
#include "../../Library/Vec2/Vec2.h"

class GameObject
{
public:

	std::string tag = "";

	Vec2 vec2 = Vec2(0, 0);

	float moveSpeed = 0;
	Vec2 vvec2 = Vec2(0, 0);

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
		return (vec2.x - rotaGraphShiftX) + hitboxOffsetLeft;
	}

	// ���[���w�肷�邱�Ƃɂ��ʒu��ݒ肷��
	virtual void SetLeft(float left)
	{
		vec2.x = (left - hitboxOffsetLeft + rotaGraphShiftX) - 1;
	}

	// �E�[���擾
	virtual float GetRight()
	{
		return (vec2.x - rotaGraphShiftX) + imageWidth - hitboxOffsetRight;
	}

	// �E�[���w�肷�邱�Ƃɂ��ʒu��ݒ肷��
	virtual void SetRight(float right)
	{
		vec2.x = (right + hitboxOffsetRight - imageWidth + rotaGraphShiftX) + 1;
	}

	// ��[���擾
	virtual float GetTop()
	{
		return vec2.y - rotaGraphShiftY + hitboxOffsetTop;
	}

	// ��[���w�肷�邱�Ƃɂ��ʒu��ݒ肷��
	virtual void SetTop(float top)
	{
		vec2.y = (top + hitboxOffsetTop + rotaGraphShiftY) + 1;
	}

	// ���[���擾����
	virtual float GetBottom()
	{
		return (vec2.y - rotaGraphShiftY) + imageHeight - hitboxOffsetBottom;
	}

	// ���[���w�肷�邱�Ƃɂ��ʒu��ݒ肷��
	virtual void SetBottom(float bottom)
	{
		vec2.y = (bottom + hitboxOffsetBottom - imageHeight + rotaGraphShiftY) - 1;
	}

	//�~�Ίp�`�̓����蔻��p�̍���
	virtual Vec2 GetLeftTop()
	{
		return (Vec2(GetLeft(), GetTop()));
	}

	//�~�Ίp�`�̓����蔻��p�̉E��
	virtual Vec2 GetRightBottom()
	{
		return (Vec2(GetRight(), GetBottom()));
	}

	// �_�ɏ��n�̂��߂�1�t���[���O�����֐��Q
	// 1�t���[���O����̈ړ��ʁix�����j
	virtual float GetDeltaX()
	{
		return vec2.x - prevX;
	}

	// 1�t���[���O����̈ړ��ʁiy�����j
	virtual float GetDeltaY()
	{
		return vec2.y - prevY;
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
		prevX = vec2.x;
		prevY = vec2.y;
		prevLeft = GetLeft();
		prevRight = GetRight();
		prevTop = GetTop();
		prevBottom = GetBottom();
	}

	virtual void Update() = 0;

	virtual void Draw() = 0;
};

#endif // !GAMEOBJECT_H_

