#include "TitleScene.h"
#include "../../../Game.h"
#include "../../../Library/DataSave/DataSave.h"
#include "../../../Library/MyMath/MyMath.h"
#include "../../../GameObject/Parent/GameObject.h"
#include "../../../Resource/Sound/SoundEffect_Object/SoundEffectObject.h"
#include "../../../Resource/Sound/BGM_Object/BGM_Object.h"
#include "../../../Library/GameManager/GameObjectManeger/GameObjectManager.h"
#include "../../../GameObject/Child/Player/Player.h"
#include "../../../GameObject/Child/Enemy/Enemy.h"
#include "../../../Library/Camera/Camera.h"
#include "../../../Resource/Map/Map.h"
#include "../../../Resource/Stage/Stage.h"
#include "../../../Resource/Effect/Child/Explo/Explo.h"
#include "../../../Library/Screen/Screen.h"
#include "../../../Library/Input/Input.h"

TitleScene::TitleScene()
{
}

void TitleScene::Init()
{
	gm.camera_ = std::make_shared<Camera>();
	//gm.map_ = std::make_shared<Map>(0, "Stage1");
	gm.stage_ = std::make_shared<Stage>("1.mv1");
	gm.game_object_manager_->add(std::make_shared<Player>(Vec3(100, 120, 100)));
	//gm.game_object_manager_->add(std::make_shared<Enemy>(Vec3(200,0, 200)));
}

void TitleScene::Update()
{
	gm.game_object_manager_->update();
	gm.camera_->update();
	gm.game_object_manager_->collide();
	gm.game_object_manager_->remove();

}

void TitleScene::Draw()
{
	/*gm.map_->DrawTerrain();*/
	gm.stage_->draw();
	gm.camera_->draw();
	gm.game_object_manager_->draw();
	//DrawString(0, 0, "Title", GetColor(255, 255, 255));
	//DrawTriangle3D(
	//	VGet(0.0f,0.0f, 0.0f),
	//	VGet(-200.0f, 200.0f, 0.0f),
	//	VGet(200.0f, 200.0f, 0.0f), GetColor(255, 255, 255), FALSE);
	//SetCameraPositionAndTarget_UpVecY(VGet(0,0,-80), VGet(0, 0, 0));
}