#ifndef PLAYING_H_
#define PLAYING_H_

#include "../../Parent/Scene.h"
#include "DxLib.h"
#include "../../../Library/NotMyLib/GameManager.h"

#include <algorithm>
#include <memory>

class Game;

class Playing :public Scene
{
public:
	Playing(Game* game);

	void Init() override;

	void Update() override;

	void Draw() override;

	GameManager& gm = GameManager::GetInstance();

private:
	int x = 0;
	Game* m_game;
};
#endif

