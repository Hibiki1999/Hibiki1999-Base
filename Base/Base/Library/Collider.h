#ifndef COLLIDER_H_
#define COLLIDER_H_

#include "Component.h"

#include "Vector3.h"

class GameObject;

class Collider : public Component
{
public:
	static const std::string& Type() { return "Collider"; }
	std::string componentType = "Collider"; // �R���|�[�l���g�̎��(Collider�ȂǑ�܂��Ȏ��)

	// �������R���X�g���N�^
	Collider(GameObject* owner) : Component(owner)
	{
	}

	// ���z�f�X�g���N�^
	~Collider()
	{
	}

	//���� collider �͑��� collider �ɐG�ꂽ�Ƃ��� OnCollisionEnter �͌Ăяo����܂��B
	virtual void OnCollisionEnter()
	{

	}
	//���� collider ������ collider �ƐG�ꍇ���̂���߂��Ƃ��� OnCollisionExit �͌Ăяo����܂��B
	virtual void OnCollisionExit()
	{

	}
	//OnCollisionStay �� rigidbody / collider ������ rigidbody / collider �ɐG��Ă���Ԗ��t���[�� 1 �x�����Ăяo����܂��B
	virtual void OnCollisionStay()
	{

	}
	//GameObject�����̃I�u�W�F�N�g�� collides�����Ƃ� OnTriggerEnter���Ăяo����܂�
	virtual void OnTriggerEnter()
	{

	}
	//Collider �� other �̃g���K�[�ɐG���̂���߂��Ƃ��� OnTriggerExit �͌Ăяo����܂��B
	virtual void OnTriggerExit()
	{

	}
	virtual void OnTriggerStay()
	{

	}
};


#endif
