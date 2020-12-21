
#include "Scene/Parent/Scene.h"
#include <DxLib.h>
#include "Resource/Image/Image.h"

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

	//’Ç‰Á‚µ‚½ƒV[ƒ“‚Í‚±‚Ì‰º‚É’è‹`
	Scene* m_title;

	Scene* m_play;

	Scene* m_ending;

private:

};
