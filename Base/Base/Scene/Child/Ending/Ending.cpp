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
	++x;
	if (x > 60)
	{
		x = 0;
		m_game->ChangeScene(m_game->m_title);
	}
}

void Ending::Draw()
{
	DrawString(0, 0, "Ending", GetColor(255, 255, 255));
}