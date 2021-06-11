#include "Camera.h"
#include "../../GameObject/Child/Player/Player.h"
#include "../GameManager/GameObjectManeger/GameObjectManager.h"
#include "../MyDraw/MyDraw.h"

Camera::Camera()
{
	Vec3 moveCamera = Vec3(0, 0, -80);
	transform_.position(moveCamera);
}

Camera::~Camera()
{
}

void Camera::update()
{
	//�v���C���[�擾
	std::shared_ptr<GameObject> player = gm.game_object_manager_->find("Player");
	if (player != nullptr) {
		//�v���C���[�ʒu�擾
		Vec3 cameraPosition = player->transform().position();
		//�����_�ύX���Ȃ����ߑ��̂ǂ���ɕۑ�
		Vec3 lookTarget = cameraPosition;
		//�v���C���[�̌��80px������
		cameraPosition.z += 400;
		cameraPosition.y += 300;
		lookTarget.y += 150;
		//�J�������W�𓱓�
		transform_.position(cameraPosition);
		//�J���������_���v���C���[�Ƀ��b�N
		look_point_ = lookTarget;
	}
}

void Camera::draw() const
{
	SetUseLighting(false);
	MyDraw::SetCameraPositionAndTarget_UpVecY(transform_.position(), look_point_);
}
