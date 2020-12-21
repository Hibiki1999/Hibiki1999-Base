#pragma once

#include "../../Parent/Scene.h"
#include "DxLib.h"

class Game;

class Playing :public Scene
{
public:
	Playing(Game* game);

	void Init() override;

	void Update() override;

	void Draw() override;

private:
	int x = 0;
	Game* m_game;
};