#include "Ending.h"
#include "../../../Game.h"

Ending::Ending(Game* game)
{
	m_game = game;
}

void Ending::Init()
{

}

void Ending::Update()
{
	if (Input::GetButtonDown(Pad::All, PAD_INPUT_1)) Game::ChangeScene(m_game->m_title);
}

void Ending::Draw()
{
	DrawString(0, 0, "Ending�V�[���BZ�L�[��Titler�V�[���Ɉڂ�B", GetColor(255, 255, 255));
}