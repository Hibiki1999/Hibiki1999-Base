#include "Title.h"
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

Title::Title(Game* game)
{
	m_game = game;//現存のGameをタイトルに代入
}

void Title::Init()
{
	DataSave::Load();
	gm.camera_ = std::make_shared<Camera>();
	gm.map_ = std::make_shared<Map>(0, "Stage1");
	gm.game_object_manager_->add(std::make_shared<Player>(Vec3(100, 0, 100)));
	gm.game_object_manager_->add(std::make_shared<Enemy>(Vec3(200,0, 200)));
}

void Title::Update()
{
	//if (Input::GetButtonDown(Pad::All, PAD_INPUT_1))Game::ChangeScene(m_game->m_play);
	gm.game_object_manager_->update();
	gm.camera_->update();
	clsDx();
	gm.game_object_manager_->collide();
	gm.game_object_manager_->remove();

}

void Title::Draw()
{
	gm.map_->DrawTerrain();
	gm.camera_->draw();
	gm.game_object_manager_->draw();
	//DrawString(0, 0, "Title", GetColor(255, 255, 255));
	//DrawTriangle3D(
	//	VGet(0.0f,0.0f, 0.0f),
	//	VGet(-200.0f, 200.0f, 0.0f),
	//	VGet(200.0f, 200.0f, 0.0f), GetColor(255, 255, 255), FALSE);
	//SetCameraPositionAndTarget_UpVecY(VGet(0,0,-80), VGet(0, 0, 0));
}