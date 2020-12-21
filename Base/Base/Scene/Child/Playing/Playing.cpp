#include "Playing.h"
#include "../../../Game.h"

Playing::Playing(Game* game)
{
	m_game = game;
}

void Playing::Init()
{

}

void Playing::Update()
{
	++x;
	if (x >= 60)
	{
		x = 0;
		m_game->ChangeScene(m_game->m_ending);
	}
}

void Playing::Draw()
{
	DrawString(0, 0, "Play", GetColor(255, 255, 255));
}