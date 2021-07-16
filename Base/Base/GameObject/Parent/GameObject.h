#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string>

#include "../../Library/MyDraw/MyDraw.h"
#include "../../Library/Collision/SphereCollision/SphereCollision.h"
#include "../../Library/Collision/CubeCollision/CubeCollision.h"
#include "../../Library/Screen/Screen.h"
#include "../../Library/GameManager/GameManager.h"
#include"../../Resource/Image/Image.h"
#include "../../Library/MyRandom/MyRandom.h"
#include "../../Library/Transform/Transform.h"

class GameObject :public std::enable_shared_from_this<GameObject>
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
	virtual void react(std::shared_ptr<GameObject> other);
	//�Փ˔���
	void collide(std::shared_ptr<GameObject> other);
	//���S����
	void die();
	//�Փ˂��Ă��邩�H
	bool is_collide(const std::shared_ptr<GameObject> other);
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
	SphereCollision collider();

	float height();
	//�ǂ̏Փ˔���
	void WallCollide();
	//�d��
	void gravity();
	//���˂��镨�̏d��
	void projectile_gravity();
	//�n�ʂɂ��邩�H
	void grounded();
	//�󒆂ɂ���̂��H
	bool isAir();
	//���̂��ŉ���
	Vec3 gravity_velo();
	//���̂���-1���|����
	void minus_gravity_velo();
	//�d�͂ɉe�����󂯂邩�𒲂ׂ�
	bool is_gravity();
	//�ǂɓ����蔻�肠�邩�ǂ���
	bool is_wallcollide();

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
	bool enable_wall_collider_{ false };
	//�Փ˔���
	SphereCollision collider_;
	CubeCollision cube_collider_;
	//���S�t���O
	bool dead_{ false };
	//�W�����v
	void Jump(float jumpPower);
	//�d�͂ɓK�p���邩
	bool enable_gravity_{ true };
	//�d��
	float gravity_power_{ -3.1f };
	//�d�͂̋���
	float max_gravity_power_ = -30.0f;

private:

	GameManager& gm = GameManager::GetInstance();

	Vec3 gravity_velocity_{ 0.0f,0.0f,0.0f };

};

#endif // !GAMEOBJECT_H_

