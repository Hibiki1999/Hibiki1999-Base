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
	//各シーンを読み込む
	sm.register_scene("TitleScene", std::make_shared<TitleScene>());
	sm.register_scene("PlayingScene", std::make_shared<PlayingScene>());
}

void Game::Init()
{
	//Input::Init();//ゲームパットを読み込む
	MyRandom::Init();//乱数を読み込む
	Image::Init();//画像を読み込む
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
	sm.update();//読み込まれるシーンの毎秒60回更新
	gm.bgm->Update();
	gm.soundEffects->remove();
	for (const auto& e : gm.effects) {
		e->Update();
	}
}

void Game::Draw()
{
	sm.draw();//更新したシーンの状況を更新
	for (const auto& e : gm.effects) {
		e->Draw();
	}
}

void Game::RegisterButton()
{
	/*
	*
	||===================================================================||
	||使えるPADボタン													 ||
	||#define XINPUT_BUTTON_DPAD_UP			(0)	// デジタル方向ボタン上	 ||
	||#define XINPUT_BUTTON_DPAD_DOWN		(1)	// デジタル方向ボタン下  ||
	||#define XINPUT_BUTTON_DPAD_LEFT		(2)	// デジタル方向ボタン左  ||
	||#define XINPUT_BUTTON_DPAD_RIGHT		(3)	// デジタル方向ボタン右	 ||
	||#define XINPUT_BUTTON_START			(4)	// STARTボタン			 ||
	||#define XINPUT_BUTTON_BACK			(5)	// BACKボタン			 ||
	||#define XINPUT_BUTTON_LEFT_THUMB		(6)	// 左スティック押し込み	 ||
	||#define XINPUT_BUTTON_RIGHT_THUMB		(7)	// 右スティック押し込み	 ||
	||#define XINPUT_BUTTON_LEFT_SHOULDER	(8)	// LBボタン				 ||
	||#define XINPUT_BUTTON_RIGHT_SHOULDER	(9)	// RBボタン				 ||
	||#define XINPUT_BUTTON_A				(12)// Aボタン				 ||
	||#define XINPUT_BUTTON_B				(13)// Bボタン				 ||
	||#define XINPUT_BUTTON_X				(14)// Xボタン				 ||
	||#define XINPUT_BUTTON_Y				(15)// Yボタン				 ||
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
