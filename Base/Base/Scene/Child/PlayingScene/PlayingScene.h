#ifndef PLAYING_SCENE_H_
#define PLAYING_SCENE_H_

#include "../../Parent/Scene.h"
#include <DxLib.h>
#include "../../../Library/GameManager/GameManager.h"
#include"../../../Resource/Map/Map.h"

#include <algorithm>
#include <memory>


class PlayingScene :public Scene
{
public:
	PlayingScene();

	~PlayingScene() {};

	void Init() override;

	void Update() override;

	void Draw() override;


private:
	GameManager&  gm = GameManager::GetInstance();

};
#endif

