#include "Title.h"
#include "../../../Game.h"
#include "../../../Library/DataSave/DataSave.h"
#include "../../../Library/Vec2/Vec2.h"

int Title::test{ 0 };

Title::Title(Game* game)
{
	m_game = game;//������Game���^�C�g���ɑ��
}

void Title::Init()
{
	DataSave::Load();
}

void Title::Update()
{
	if (Input::GetButtonDown(Pad::All, PAD_INPUT_1))Game::ChangeScene(m_game->m_play);
}

void Title::Draw()
{
	DrawString(0, 0, "title�V�[���BZ�L�[��Play�V�[���̈ڂ�B", GetColor(255, 255, 255));
	DrawString(0, 20, std::to_string(test).c_str(), GetColor(255, 255, 255));
}