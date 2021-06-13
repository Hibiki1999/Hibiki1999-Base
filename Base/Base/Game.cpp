#include "Game.h"
#include "Scene/Child/Title/Title.h"
#include "Scene/Child/Playing/Playing.h"
#include "Scene/Child/Ending/Ending.h"
#include "Resource/Sound/BGM_Object/BGM_Object.h"
#include "Resource/Sound/SoundEffect_Object/SoundEffectObject.h"
#include "Library/GameManager/GameObjectManeger/GameObjectManager.h"

Scene* scenes;

Game::Game()
{
	//�e�V�[����ǂݍ���
	m_title = new Title(this);
	m_play = new Playing(this);
	m_ending = new Ending(this);
	RegisterButton();
}

void Game::Init()
{
	Input::Init();//�Q�[���p�b�g��ǂݍ���
	MyRandom::Init();//������ǂݍ���
	Image::Init();//�摜��ǂݍ���
	gm.bgm = std::make_shared<BGM_Object>();
	gm.game_object_manager_ = std::make_shared<GameObjectManager>();
	MyDraw::InitMyDraw();
#ifdef _DEBUG

	Sound::Init();//�f�o�O���̂݉����̃p�X���m�F����

#endif // _DEBUG
	Game::ChangeScene(m_title);
}

void Game::Update()
{
	if (gm.bgm != nullptr)	gm.bgm->Update();
	Input::Update();
	scenes->Update();//�ǂݍ��܂��V�[���̖��b60��X�V
	for (const auto& se : gm.soundEffects)
	{
		se->Update();
	}
	gm.EraseRemoveIf(gm.soundEffects, [](std::shared_ptr<SoundEffectObject>& ptr) {return ptr->isDead; });

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

void Game::RegisterButton()
{
	/*
	* 
	||===================================================================||
	||�g����{�^��													     ||
	||PAD_INPUT_DOWN�@	// ���`�F�b�N�}�X�N(���L�[ or �e���L�[�̂Q�L�[)  ||
	||PAD_INPUT_LEFT�@	// ���`�F�b�N�}�X�N(���L�[ or �e���L�[�̂S�L�[)  ||
	||PAD_INPUT_RIGHT�@	// ���`�F�b�N�}�X�N(�E�L�[ or �e���L�[�̂U�L�[)  ||
	||PAD_INPUT_UP�@	// ���`�F�b�N�}�X�N(��L�[ or �e���L�[�̂W�L�[)  ||
	||PAD_INPUT_1�@	    // 1�{�^���`�F�b�N�}�X�N(�y�L�[)				 ||
	||PAD_INPUT_2�@	    // 2�{�^���`�F�b�N�}�X�N(�w�L�[)				 ||
	||PAD_INPUT_3�@	    // 3�{�^���`�F�b�N�}�X�N(�b�L�[)				 ||
	||PAD_INPUT_4�@	    // 4�{�^���`�F�b�N�}�X�N(�`�L�[)				 ||
	||PAD_INPUT_5�@	    // 5�{�^���`�F�b�N�}�X�N(�r�L�[)				 ||
	||PAD_INPUT_6�@	    // 6�{�^���`�F�b�N�}�X�N(�c�L�[)				 ||
	||PAD_INPUT_7�@	    // 7�{�^���`�F�b�N�}�X�N(�p�L�[)				 ||
	||PAD_INPUT_8�@	    // 8�{�^���`�F�b�N�}�X�N(�v�L�[)				 ||
	||PAD_INPUT_9�@	    // 9�{�^���`�F�b�N�}�X�N(�d�r�b�L�[)			 ||
	||PAD_INPUT_10�@	// 10�{�^���`�F�b�N�}�X�N(�X�y�[�X�L�[)			 ||
	||===================================================================||
	*
	*/

	Input::RegisterButton("Forward", PAD_INPUT_UP);
	Input::RegisterButton("Forward", PAD_INPUT_8);
	Input::RegisterButton("Backward", PAD_INPUT_DOWN);
	Input::RegisterButton("Backward", PAD_INPUT_5);
	Input::RegisterButton("ToLeft", PAD_INPUT_LEFT);
	Input::RegisterButton("ToLeft", PAD_INPUT_4);
	Input::RegisterButton("ToRight", PAD_INPUT_RIGHT);
	Input::RegisterButton("ToRight", PAD_INPUT_6);
	Input::RegisterButton("Jump", PAD_INPUT_10);
}
