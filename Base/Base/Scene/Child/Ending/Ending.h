#pragma once
#include "../../Parent/Scene.h"
#include "DxLib.h"

class Game;

class Ending :public Scene
{
private:
	int x = 0;
	Game* m_game;

public:
	Ending(Game* game);

	void Init() override;

	void Update() override;

	void Draw() override;
};