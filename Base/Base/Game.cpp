#include "Game.h"
#include "Scene/Child/Title/Title.h"
#include "Scene/Child/Playing/Playing.h"
#include "Scene/Child/Ending/Ending.h"

Scene* scenes;

Game::Game()
{
	//�e�V�[����ǂݍ���
	m_title = new Title(this);
	m_play = new Playing(this);
	m_ending = new Ending(this);
}

void Game::Init()
{
	Image::Init();//�摜��ǂݍ���
	Game::ChangeScene(m_title);
	
}

void Game::Update()
{
	scenes->Update();//�ǂݍ��܂��V�[���̖��b60��X�V
}

void Game::Draw()
{
	scenes->Draw();//�X�V�����V�[���̏󋵂��X�V
}

void Game::ChangeScene(Scene* scene)//�V�[����ς���Ƃ��ɁA�����ɌĂ΂��
{
	scenes = scene;//�Ă΂��̎��̃V�[�����`
	scenes->Init();//�ǂݍ��܂��V�[���̏�����
}
