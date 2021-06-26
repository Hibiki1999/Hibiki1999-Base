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
	//各シーンを読み込む
	sm.register_scene("TitleScene", std::make_shared<TitleScene>());
	sm.register_scene("PlayingScene", std::make_shared<PlayingScene>());
	RegisterButton();
}

void Game::Init()
{
	Input::Init();//ゲームパットを読み込む
	MyRandom::Init();//乱数を読み込む
	Image::Init();//画像を読み込む
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
	||使えるボタン													     ||
	||PAD_INPUT_DOWN　	// ↓チェックマスク(下キー or テンキーの２キー)  ||
	||PAD_INPUT_LEFT　	// ←チェックマスク(左キー or テンキーの４キー)  ||
	||PAD_INPUT_RIGHT　	// →チェックマスク(右キー or テンキーの６キー)  ||
	||PAD_INPUT_UP　	// ↑チェックマスク(上キー or テンキーの８キー)  ||
	||PAD_INPUT_1　	    // 1ボタンチェックマスク(Ｚキー)				 ||
	||PAD_INPUT_2　	    // 2ボタンチェックマスク(Ｘキー)				 ||
	||PAD_INPUT_3　	    // 3ボタンチェックマスク(Ｃキー)				 ||
	||PAD_INPUT_4　	    // 4ボタンチェックマスク(Ａキー)				 ||
	||PAD_INPUT_5　	    // 5ボタンチェックマスク(Ｓキー)				 ||
	||PAD_INPUT_6　	    // 6ボタンチェックマスク(Ｄキー)				 ||
	||PAD_INPUT_7　	    // 7ボタンチェックマスク(Ｑキー)				 ||
	||PAD_INPUT_8　	    // 8ボタンチェックマスク(Ｗキー)				 ||
	||PAD_INPUT_9　	    // 9ボタンチェックマスク(ＥＳＣキー)			 ||
	||PAD_INPUT_10　	// 10ボタンチェックマスク(スペースキー)			 ||
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
