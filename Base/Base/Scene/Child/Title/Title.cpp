#include "Title.h"
#include "../../../Game.h"

Title::Title(Game* game)
{
	m_game = game;//現存のGameをタイトルに代入
}

void Title::Init()
{

}

void Title::Update()
{
	if (Input::GetButton(Pad::Key, PAD_INPUT_1))
	{
		Game::ChangeScene(m_game->m_play);
	}
}

void Title::Draw()
{
	DrawString(0, 0, "titleシーンです。", GetColor(255, 255, 255));
}