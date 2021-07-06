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
	angle -= mouseMovement.x * MyMath::Deg2Rad;
	angleY -= mouseMovement.y * MyMath::Deg2Rad;

	if (angleY > MyMath::PI / 2.3f)angleY = MyMath::PI / 2.3f;
	else if (angleY < -1.4f)angleY = -1.4f;

	//プレイヤー取得
	std::shared_ptr<GameObject> player = gm.game_object_manager_->find("Player");
	if (player != nullptr) {
		Vec3 playerPos = player->transform().position();
		Vec3 CameraPosition;
		Vec3 CameraLookAtPosition;
		FollowCamera(playerPos, 120.0f, 600.0f, &CameraPosition, &CameraLookAtPosition);

		transform_.position(CameraPosition);

		look_point_ = CameraLookAtPosition;
	}
	MyDraw::CameraAngleHRotate = GetCameraAngleHRotate();
	MyDraw::CameraPos = transform_.position();
}

void Camera::draw() const
{
	SetUseLighting(false);
	MyDraw::SetCameraPositionAndTarget_UpVecY(transform_.position(), look_point_);
}

Vec3 Camera::front_vec()
{
	VECTOR vec = GetCameraFrontVector();
	Vec3 vvec;
	vvec.ConvBack(vec);
	return vvec;
}

Vec3 Camera::left_vec()
{
	VECTOR vec = GetCameraLeftVector();
	Vec3 vvec;
	vvec.ConvBack(vec);
	return vvec;
}

Vec3 Camera::front_vec_mute_y()
{
	float angle = GetCameraAngleHRotate();
	Vec3 front = Vec3(
		std::sin(angle),
		0.0f,
		std::cos(angle)
	);
	return front;
}

Vec3 Camera::left_vec_mute_y()
{
	float angle = GetCameraAngleHRotate();
	angle -= (MyMath::PI / 2);
	Vec3 left = Vec3(
		std::sin(angle),
		0.0f,
		std::cos(angle)
	);
	return left;
}


void Camera::FollowCamera(Vec3 targetPos, float targetOffsetHight, float length, Vec3* CameraPos, Vec3* CameraLookPosition)
{
	Vec3  TempPosition1;
	Vec3  TempPosition2;
	Vec3  CameraPosition;
	Vec3  CameraLookAtPosition;

	CameraLookAtPosition = targetPos;
	CameraLookAtPosition.y += targetOffsetHight;

	TempPosition1.x = 0.0f;
	TempPosition1.y = std::sin(angleY) * length;
	TempPosition1.z = -(std::cos(angleY) * length);

	float SinParam = std::sin(angle);
	float CosParam = std::cos(angle);
	TempPosition2.x = CosParam * TempPosition1.x - SinParam * TempPosition1.z;
	TempPosition2.y = TempPosition1.y;
	TempPosition2.z = SinParam * TempPosition1.x + CosParam * TempPosition1.z;

	*CameraPos = TempPosition2 + CameraLookAtPosition;
	*CameraLookPosition = CameraLookAtPosition;
}

//Vec3 cameraOffset = Vec3(
//	std::sin(angle) * 600.0f,
//	600.0f,
//	std::cos(angle) * 600.0f
//);

//playerPos += cameraOffset;

//transform_.position(playerPos);
//look_point_ = player->transform().position();
//////プレイヤー位置取得
////Vec3 cameraPosition = player->transform().position();
//////注視点変更しないため他のどころに保存
////Vec3 lookTarget = cameraPosition;
//////プレイヤーの後ろ80px下がる
////cameraPosition.z -= 400;
////cameraPosition.y += 500;
////lookTarget.y += 150;
//////カメラ座標を導入
////transform_.position(cameraPosition);
//////カメラ注視点をプレイヤーにロック
////look_point_ = lookTarget;