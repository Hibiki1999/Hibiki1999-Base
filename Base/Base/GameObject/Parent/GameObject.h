#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string>

#include "../../Library/Collision/SphereCollision/SphereCollision.h"
#include "../../Library/Screen/Screen.h"
#include "../../Library/Input/Input.h"
#include "../../Library/GameManager/GameManager.h"
#include"../../Resource/Image/Image.h"
#include "../../Library/MyRandom/MyRandom.h"
#include "../../Library/Transform/Transform.h"

class GameObject
{
public:

public:
	//�R���X�g���N�^
	GameObject() = default;
	//���z�f�X�g���N�^
	virtual ~GameObject() = default;
	//�X�V
	virtual void update();
	//�`��
	virtual void draw() const;
	//�������̕`��
	virtual void draw_transparent() const;
	//GUI�̕`��
	virtual void draw_gui() const;
	//�Փ˃��A�N�V����
	virtual void react(GameObject& other);
	//�Փ˔���
	void collide(GameObject& other);
	//���S����
	void die();
	//�Փ˂��Ă��邩�H
	bool is_collide(const GameObject& other) const;
	//���S���Ă��邩�H
	bool is_dead() const;
	//���O���擾
	const std::string& name() const;
	//�^�O�����擾
	const std::string& tag() const;
	//�g�����X�t�H�[�����擾(Const��)
	const Transform& transform() const;
	//�g�����X�t�H�[�����擾
	Transform& transform();
	//�ړ��ʂ��擾
	Vec3 velocity() const;
	//�Փ˔���f�[�^���擾
	SphereCollision collider() const;

	//�R�s�[�֎~
	GameObject(const GameObject& other) = delete;
	GameObject& operator = (const GameObject& other) = delete;

protected:
	
	//�^�O��
	std::string tag_;
	//���O
	std::string name_;
	//�g�����X�t�H�[��
	Transform transform_;
	//�ړ���
	Vec3 velocity_{ 0.0f,0.0f,0.0f };
	//�Փ˔��肪�L����?
	bool enable_collider_{ true };
	//�Փ˔���
	SphereCollision collider_;
	//���S�t���O
	bool dead_{ false };

};

#endif // !GAMEOBJECT_H_

