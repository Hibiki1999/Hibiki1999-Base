#include "PlayingScene.h"
#include "../../../Game.h"
#include "../../../Resource/Map/Map.h"
#include "../../../Resource/Sound/SoundEffect_Object/SoundEffectObject.h"

PlayingScene::PlayingScene()
{
}

void PlayingScene::Init()
{

}

void PlayingScene::Update()
{
	//if (Input::GetButtonDown(Pad::All, PAD_INPUT_1)) Game::ChangeScene(m_game->m_ending);
}

void PlayingScene::Draw()
{
	DrawString(0, 0, "Play�V�[���BZ�L�[��Ending�V�[���Ɉڂ�B", GetColor(255, 255, 255));
}