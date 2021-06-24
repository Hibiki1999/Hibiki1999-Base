#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

#include <memory>
#include <DxLib.h>

#include "../../Parent/Scene.h"
#include "../../../Library/GameManager/GameManager.h"
#include "../../../Library/Screen/Screen.h"
#include "../../../Library/Input/Input.h"

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

};

#endif // !TITLE_H_
