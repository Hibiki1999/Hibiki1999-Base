#include "Camera.h"
#include "../../GameObject/Child/Player/Player.h"
#include "../GameManager/GameObjectManeger/GameObjectManager.h"
#include "../MyDraw/MyDraw.h"
#include "../Input/Input.h"

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
	Vec2 mouseMovement;
	gm.input->IsMouseMoving(&mouseMovement);
	angle += mouseMovement.x * MyMath::Deg2Rad;
	angleY += mouseMovement.y * MyMath::Deg2Rad;

	//プレイヤー取得
	std::shared_ptr<GameObject> player = gm.game_object_manager_->find("Player");
	if (player != nullptr) {
		Vec3 playerPosition = player->transform().position();
		Vec3 cameraOffSet = Vec3(300, 200, 300);
		Vec3 forward = Vec3(0.0f, 0.0f, 1.0f);
		playerPosition = (playerPosition + cameraOffSet) + euler(Vec3(angle, angleY, 0)) * forward * 600.0f;

		transform_.position(playerPosition);
		look_point_ = player->transform().position();
		////プレイヤー位置取得
		//Vec3 cameraPosition = player->transform().position();
		////注視点変更しないため他のどころに保存
		//Vec3 lookTarget = cameraPosition;
		////プレイヤーの後ろ80px下がる
		//cameraPosition.z -= 400;
		//cameraPosition.y += 500;
		//lookTarget.y += 150;
		////カメラ座標を導入
		//transform_.position(cameraPosition);
		////カメラ注視点をプレイヤーにロック
		//look_point_ = lookTarget;
	}
	MyDraw::CameraAngleHRotate = GetCameraAngleHRotate();
	MyDraw::CameraPos = transform_.position();
}

void Camera::draw() const
{
	SetUseLighting(false);
	MyDraw::SetCameraPositionAndTarget_UpVecY(transform_.position(), look_point_);
}

Vec3 Camera::euler(Vec3 vec)
{
	Vec3 v = vec;
	float c1 = std::cos(v.x * 0.5f);
	float c2 = std::cos(v.y * 0.5f);
	float c3 = std::cos(v.z * 0.5f);
	float s1 = std::sin(v.x * 0.5f);
	float s2 = std::sin(v.y * 0.5f);
	float s3 = std::sin(v.z * 0.5f);
	float x = s1 * c2 * c3 + c1 * s2 * s3;
	float y = c1 * s2 * c3 - s1 * c2 * s3;
	float z = c1 * c2 * s3 - s1 * s2 * c3;
	//float w = c1 * c2 * c3 + s1 * s2 * s3;
	return Vec3(x, y, z);
}
