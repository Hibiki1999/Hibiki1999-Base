#ifndef GAME_H_
#define GAME_H_

#include <DxLib.h>

#include "Scene/Parent/Scene.h"
#include "Resource/Image/Image.h"
#include "Resource/Sound/Sound.h"
#include "Library/Input/Input.h"
#include "Library/MyRandom/MyRandom.h"
#include "Library/GameManager/GameManager.h"

class Title;
class Play;
class Ending;

class Game
{
public:
	Game();

	void Init();

	void Update();

	void Draw();

	static void ChangeScene(Scene* newScene);

	//追加したシーンはこの下に定義
	Scene* m_title;

	Scene* m_play;

	Scene* m_ending;

private:
	GameManager& gm = GameManager::GetInstance();
};
#endif // !GAME_H_