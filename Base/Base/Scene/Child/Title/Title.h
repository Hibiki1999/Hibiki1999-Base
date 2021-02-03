#ifndef TITLE_H_
#define TITLE_H_

#include <memory>

#include "../../Parent/Scene.h"
#include "DxLib.h"

class Game;

class Title :public Scene
{
public:
	Title(Game* game);//Game* ���g���āA������Game��ǂݍ��ށA*(�|�C���^���Ȃ��ƁA�V����Game����������Ă��܂�)
	
	~Title() {};

	void Init() override;

	void Update() override;

	void Draw() override;

private:

	Game* m_game;//�^�C�g���ɃQ�[���̃V�[���ς��@�\���g����悤�ɂ��邽�߂ɒ�`
};

#endif // !TITLE_H_
