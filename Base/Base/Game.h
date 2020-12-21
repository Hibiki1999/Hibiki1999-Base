
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

	//追加したシーンはこの下に定義
	Scene* m_title;

	Scene* m_play;

	Scene* m_ending;

private:

};
