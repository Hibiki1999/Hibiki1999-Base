#ifndef GAME_H_
#define GAME_H_

#include "Scene/Parent/Scene.h"
#include <DxLib.h>
#include "Resource/Image/Image.h"
#include "Resource/Sound/Sound.h"
#include "Library/Input/Input.h"
#include "Library/MyRandom/MyRandom.h"

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

	//í«â¡ÇµÇΩÉVÅ[ÉìÇÕÇ±ÇÃâ∫Ç…íËã`
	Scene* m_title;

	Scene* m_play;

	Scene* m_ending;

private:

};
#endif // !GAME_H_