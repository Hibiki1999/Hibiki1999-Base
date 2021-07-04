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
#include "Library/Input/Input.h"

Game::Game()
{
	//�e�V�[����ǂݍ���
	sm.register_scene("TitleScene", std::make_shared<TitleScene>());
	sm.register_scene("PlayingScene", std::make_shared<PlayingScene>());
}

void Game::Init()
{
	//Input::Init();//�Q�[���p�b�g��ǂݍ���
	MyRandom::Init();//������ǂݍ���
	Image::Init();//�摜��ǂݍ���
	MyDraw::InitMyDraw();
	gm.input = std::make_shared<Input>();
	RegisterButton();
	gm.bgm = std::make_shared<BGM_Object>();
	gm.game_object_manager_ = std::make_shared<GameObjectManager>();
	gm.soundEffects = std::make_shared<SoundEffectManager>();
	gm.data_save_ = std::make_shared<DataSave>();
	sm.change_scene("TitleScene");
}

void Game::Update()
{
	//Input::Update();
	gm.input->Update();
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
	||�g����PAD�{�^��													 ||
	||#define XINPUT_BUTTON_DPAD_UP			(0)	// �f�W�^�������{�^����	 ||
	||#define XINPUT_BUTTON_DPAD_DOWN		(1)	// �f�W�^�������{�^����  ||
	||#define XINPUT_BUTTON_DPAD_LEFT		(2)	// �f�W�^�������{�^����  ||
	||#define XINPUT_BUTTON_DPAD_RIGHT		(3)	// �f�W�^�������{�^���E	 ||
	||#define XINPUT_BUTTON_START			(4)	// START�{�^��			 ||
	||#define XINPUT_BUTTON_BACK			(5)	// BACK�{�^��			 ||
	||#define XINPUT_BUTTON_LEFT_THUMB		(6)	// ���X�e�B�b�N��������	 ||
	||#define XINPUT_BUTTON_RIGHT_THUMB		(7)	// �E�X�e�B�b�N��������	 ||
	||#define XINPUT_BUTTON_LEFT_SHOULDER	(8)	// LB�{�^��				 ||
	||#define XINPUT_BUTTON_RIGHT_SHOULDER	(9)	// RB�{�^��				 ||
	||#define XINPUT_BUTTON_A				(12)// A�{�^��				 ||
	||#define XINPUT_BUTTON_B				(13)// B�{�^��				 ||
	||#define XINPUT_BUTTON_X				(14)// X�{�^��				 ||
	||#define XINPUT_BUTTON_Y				(15)// Y�{�^��				 ||
	||===================================================================||
	*
	*/
	gm.input->RegisterButton("TEST", XINPUT_BUTTON_A);
	//Input::RegisterButton("Forward", PAD_INPUT_UP);
	//Input::RegisterButton("Forward", PAD_INPUT_8);
	//Input::RegisterButton("Backward", PAD_INPUT_DOWN);
	//Input::RegisterButton("Backward", PAD_INPUT_5);
	//Input::RegisterButton("ToLeft", PAD_INPUT_LEFT);
	//Input::RegisterButton("ToLeft", PAD_INPUT_4);
	//Input::RegisterButton("ToRight", PAD_INPUT_RIGHT);
	//Input::RegisterButton("ToRight", PAD_INPUT_6);
	//Input::RegisterButton("Jump", PAD_INPUT_10);
}
