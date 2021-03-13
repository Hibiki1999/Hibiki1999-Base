#ifndef TITLE_H_
#define TITLE_H_

#include <memory>
#include <DxLib.h>

#include "../../Parent/Scene.h"
#include "../../../Library/GameManager/GameManager.h"
#include "../../../Library/Screen/Screen.h"
#include "../../../Library/Vec2/Vec2.h"
#include "../../../Library/Input/Input.h"

class Game;

class Title :public Scene
{
public:
	Title(Game* game);//Game* を使って、現存のGameを読み込む、*(ポインタがないと、新しいGameが生成されてしまう)

	~Title() {};

	void Init() override;

	void Update() override;

	void Draw() override;

	static int test;
private:
	
	Game* m_game;//タイトルにゲームのシーン変え機能を使えるようにするために定義

	Vec2 testvec = Vec2(Screen::Width / 2, Screen::Height / 2);

	float r = 64.0f;
};

#endif // !TITLE_H_
