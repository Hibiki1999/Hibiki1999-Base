#include "Playing.h"
#include "../../../Game.h"

Playing::Playing(Game* game)
{
	m_game = game;
	gm.map = std::make_shared<Map>(0, "stage1");

}

void Playing::Init()
{
	Camera::LookAt(x, y);
}

void Playing::Update()
{
	if (Input::GetButton(PAD_INPUT_DOWN))
	{
		y+=5;
	}
	if (Input::GetButton(PAD_INPUT_UP))
	{
		y-=5;
	}
	if (Input::GetButton(PAD_INPUT_RIGHT))
	{
		x+=5;
	}
	if (Input::GetButton(PAD_INPUT_LEFT))
	{
		x-=5;
	}
	Camera::LookAt(x, y);
	gm.map->Scroll(x, y);
}

void Playing::Draw()
{
	gm.map->DrawTerrain();
	DrawString(0, 0, "Play", GetColor(255, 255, 255));

}