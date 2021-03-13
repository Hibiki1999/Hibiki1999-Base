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
	Title(Game* game);//Game* ���g���āA������Game��ǂݍ��ށA*(�|�C���^���Ȃ��ƁA�V����Game����������Ă��܂�)

	~Title() {};

	void Init() override;

	void Update() override;

	void Draw() override;

	static int test;
private:
	
	Game* m_game;//�^�C�g���ɃQ�[���̃V�[���ς��@�\���g����悤�ɂ��邽�߂ɒ�`

	Vec2 testvec = Vec2(Screen::Width / 2, Screen::Height / 2);

	float r = 64.0f;
};

#endif // !TITLE_H_
