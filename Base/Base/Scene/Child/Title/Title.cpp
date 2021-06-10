#include "Title.h"
#include "../../../Game.h"
#include "../../../Library/DataSave/DataSave.h"
#include "../../../Library/MyMath/MyMath.h"
#include "../../../GameObject/Parent/GameObject.h"
#include "../../../Resource/Sound/SoundEffect_Object/SoundEffectObject.h"
#include "../../../Resource/Sound/BGM_Object/BGM_Object.h"

Title::Title(Game* game)
{
	m_game = game;//Œ»‘¶‚ÌGame‚ðƒ^ƒCƒgƒ‹‚É‘ã“ü
}

void Title::Init()
{
	DataSave::Load();


}

void Title::Update()
{
	if (Input::GetButtonDown(Pad::All, PAD_INPUT_1))Game::ChangeScene(m_game->m_play);
}

void Title::Draw()
{
	SetFontSize(64);
	DrawString(0, 0, "Title", GetColor(255, 255, 255));
	DrawTriangle3D(
		VGet(0.0f,0.0f, 0.0f),
		VGet(-200.0f, 200.0f, 0.0f),
		VGet(200.0f, 200.0f, 0.0f), GetColor(255, 255, 255), FALSE);
	SetCameraPositionAndTarget_UpVecY(VGet(0,0,0), VGet(0, 0, 0));
}