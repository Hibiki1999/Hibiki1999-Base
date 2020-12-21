#pragma once

#include "../../Parent/Scene.h"
#include "DxLib.h"

class Game;

class Title :public Scene
{
public:
	Title(Game* game);//Game* を使って、現存のGameを読み込む、*(ポインタがないと、新しいGameが生成されてしまう)

	void Init() override;

	void Update() override;

	void Draw() override;

private:

	int x = 0;//テスト用

	Game* m_game;//タイトルにゲームのシーン変え機能を使えるようにするために定義
};