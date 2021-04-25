#include "Title.h"
#include "../../../Game.h"
#include "../../../Library/DataSave/DataSave.h"
#include "../../../Library/MyMath/MyMath.h"
#include "../../../GameObject/Parent/GameObject.h"
#include "../../../Resource/Sound/SoundEffect_Object/SoundEffectObject.h"
#include "../../../Resource/Sound/BGM_Object/BGM_Object.h"

int Title::test{ 0 };

Title::Title(Game* game)
{
	m_game = game;//現存のGameをタイトルに代入
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
	DrawString(0, 0, "titleシーン。ZキーでPlayシーンの移る。", GetColor(255, 255, 255));
	DrawString(0, 20, std::to_string(test).c_str(), GetColor(255, 255, 255));
}