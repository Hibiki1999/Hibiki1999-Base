#ifndef PLAYING_H_
#define PLAYING_H_

#include "../../Parent/Scene.h"
#include "DxLib.h"
#include "../../../Library/GameManager/GameManager.h"
#include"../../../Resource/Map/Map.h"

#include <algorithm>
#include <memory>

class Game;

class Playing :public Scene
{
public:
	Playing(Game* game);

	~Playing() {};

	void Init() override;

	void Update() override;

	void Draw() override;

	GameManager& gm = GameManager::GetInstance();

private:

	Game* m_game;
};
#endif

