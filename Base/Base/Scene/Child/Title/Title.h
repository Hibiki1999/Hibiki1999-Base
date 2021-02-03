#ifndef TITLE_H_
#define TITLE_H_

#include <memory>

#include "../../Parent/Scene.h"
#include "DxLib.h"

class Game;

class Title :public Scene
{
public:
	Title(Game* game);//Game* を使って、現存のGameを読み込む、*(ポインタがないと、新しいGameが生成されてしまう)
	
	~Title() {};

	void Init() override;

	void Update() override;

	void Draw() override;

private:

	Game* m_game;//タイトルにゲームのシーン変え機能を使えるようにするために定義
};

#endif // !TITLE_H_
