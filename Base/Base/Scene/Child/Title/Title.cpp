#include "Title.h"
#include "../../../Game.h"

Title::Title(Game* game)
{
	m_game = game;//������Game���^�C�g���ɑ��
}

void Title::Init()
{

}

void Title::Update()
{
	++x;
	if (x >= 60)
	{
		x = 0;
		m_game->ChangeScene(m_game->m_play);//�V�[����ς���(�ڕW�V�[���̓v���C�V�[��)
	}
}

void Title::Draw()
{
	DrawString(0, 0, "title�V�[���ł��B", GetColor(255, 255, 255));
}