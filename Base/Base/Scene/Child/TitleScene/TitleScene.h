#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

#include <memory>
#include <DxLib.h>

#include "../../Parent/Scene.h"
#include "../../../Library/GameManager/GameManager.h"

#include "../../../Library/Transform/Vec2/Vec2.h"
	

class TitleScene :public Scene
{
public:
	TitleScene();//Game* ���g���āA������Game��ǂݍ��ށA*(�|�C���^���Ȃ��ƁA�V����Game����������Ă��܂�)

	~TitleScene() {};

	void Init() override;

	void Update() override;

	void Draw() override;


private:
	GameManager& gm = GameManager::GetInstance();

	int i = 0;
};

#endif // !TITLE_H_
