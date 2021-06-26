#include "Game.h"
#include "Scene/Child/TitleScene/TitleScene.h"
#include "Scene/Child/PlayingScene/PlayingScene.h"
#include "Resource/Sound/BGM_Object/BGM_Object.h"
#include "Resource/Sound/SoundEffectManager.h"
#include "Library/GameManager/GameObjectManeger/GameObjectManager.h"
#include "Library/DataSave/DataSave.h"
#include "Library/MyRandom/MyRandom.h"
#include "Library/MyDraw/MyDraw.h"
#include "Resource/Image/Image.h"
#include "Resource/Effect/Parents/EffectParent.h"

Game::Game()
{
	//�e�V�[����ǂݍ���
	sm.register_scene("TitleScene", std::make_shared<TitleScene>());
	sm.register_scene("PlayingScene", std::make_shared<PlayingScene>());
	RegisterButton();
}

void Game::Init()
{
	Input::Init();//�Q�[���p�b�g��ǂݍ���
	MyRandom::Init();//������ǂݍ���
	Image::Init();//�摜��ǂݍ���
	MyDraw::InitMyDraw();
	gm.bgm = std::make_shared<BGM_Object>();
	gm.game_object_manager_ = std::make_shared<GameObjectManager>();
	gm.soundEffects = std::make_shared<SoundEffectManager>();
	gm.data_save_ = std::make_shared<DataSave>();
	sm.change_scene("TitleScene");
}

void Game::Update()
{
	Input::Update();
	gm.soundEffects->update();
	sm.update();//�ǂݍ��܂��V�[���̖��b60��X�V
	gm.bgm->Update();
	gm.soundEffects->remove();
	for (const auto& e : gm.effects) {
		e->Update();
	}
}

void Game::Draw()
{
	sm.draw();//�X�V�����V�[���̏󋵂��X�V
	for (const auto& e : gm.effects) {
		e->Draw();
	}
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
