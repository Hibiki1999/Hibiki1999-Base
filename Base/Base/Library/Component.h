#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "Vector3.h"

class GameObject; //�O���錾


class Component
{
public:
	static const std::string& Type() { return "Component"; } // GetComponent�Ɏg��

	union { // �����p��union�e�N�j�b�N https://inemaru.hatenablog.com/entry/2016/03/02/005408
		Vector3 position; // ���W
		struct { 
			float x;
			float y;
			float z;
		}; // XYZ���W  [�������p�̂Ƃ�] https://code.i-harness.com/ja-jp/q/4d437c
		std::array<float, 3> xyz; // float xyz[3];�Ɠ����Ӗ� float 3�Ԃ�̃f�[�^�T�C�Y��x,y,z 3�Ԃ�ƈ�v����̂Ł�union�ŋ��p
	}; // union�͈قȂ镡���̂��̂���������̓���̔Ԓn�Ɋ��蓖�Ă����x,y,z�����ċL�q����̖ʓ|�ȂƂ��z��xyz[3]��for��i=0�`3�ŉ񂹂�

	GameObject* gameObject; //���g�����L����[�I�[�i�[��GameObject�ւ̃|�C���^
	std::string tag = ""; //�^�O
	std::string componentType = ""; // �R���|�[�l���g�̎��(Collider�ȂǑ�܂��Ȏ��)
	
	// �R���|�[�l���g���Q�b�g����
	template<typename GameObjectType>
	GameObjectType *GetComponent();

	// �������R���X�g���N�^
	Component(GameObject* owner) : gameObject{ owner }
	{
	}

	// ���z�f�X�g���N�^
	~Component()
	{
	}
	// �X�V����
	virtual void Update()
	{
	}
};


#endif
