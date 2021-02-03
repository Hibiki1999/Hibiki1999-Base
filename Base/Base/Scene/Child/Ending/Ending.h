#ifndef ENDING_H_
#define ENDING_H_

#include "../../Parent/Scene.h"
#include "DxLib.h"

class Game;

class Ending :public Scene
{
public:
	Ending(Game* game);

	~Ending() {};

	void Init() override;

	void Update() override;

	void Draw() override;

private:

	Game* m_game;
};

#endif // !ENDING_H_

