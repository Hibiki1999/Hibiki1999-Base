#include "Playing.h"
#include "../../../Game.h"

Playing::Playing(Game* game)
{
	m_game = game;
	gm.map = std::make_shared<Map>(0, "stage1");
}

void Playing::Init()
{

}

void Playing::Update()
{
	if (Input::GetButtonDown(Pad::All, PAD_INPUT_1)) Game::ChangeScene(m_game->m_ending);
}

void Playing::Draw()
{
	DrawString(0, 0, "Play�V�[���BZ�L�[��Ending�V�[���Ɉڂ�B", GetColor(255, 255, 255));
}