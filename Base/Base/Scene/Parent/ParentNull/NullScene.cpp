#include "NullScene.h"
#include <DxLib.h>

void NullScene::Init()
{
}

void NullScene::Update()
{
}

void NullScene::Draw()
{
	DrawString(0, 0, "NullScene�ł���B�ǂ��̃X�y���Ԉ���Ă܂���B", GetColor(255, 255, 255));
}

void NullScene::Finalize()
{
}
