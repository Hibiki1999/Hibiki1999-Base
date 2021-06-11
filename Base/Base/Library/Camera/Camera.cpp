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
	//プレイヤー取得
	std::shared_ptr<GameObject> player = gm.game_object_manager_->find("Player");
	if (player != nullptr) {
		//プレイヤー位置取得
		Vec3 cameraPosition = player->transform().position();
		//注視点変更しないため他のどころに保存
		Vec3 lookTarget = cameraPosition;
		//プレイヤーの後ろ80px下がる
		cameraPosition.z += 400;
		cameraPosition.y += 300;
		lookTarget.y += 150;
		//カメラ座標を導入
		transform_.position(cameraPosition);
		//カメラ注視点をプレイヤーにロック
		look_point_ = lookTarget;
	}
}

void Camera::draw() const
{
	SetUseLighting(false);
	MyDraw::SetCameraPositionAndTarget_UpVecY(transform_.position(), look_point_);
}
