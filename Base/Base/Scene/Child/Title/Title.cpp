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
	++x;
	if (x >= 60)
	{
		x = 0;
		m_game->ChangeScene(m_game->m_play);//シーンを変える(目標シーンはプレイシーン)
	}
}

void Title::Draw()
{
	DrawString(0, 0, "titleシーンです。", GetColor(255, 255, 255));
}