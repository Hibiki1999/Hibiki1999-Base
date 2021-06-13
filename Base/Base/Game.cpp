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
	//各シーンを読み込む
	m_title = new Title(this);
	m_play = new Playing(this);
	m_ending = new Ending(this);
	RegisterButton();
}

void Game::Init()
{
	Input::Init();//ゲームパットを読み込む
	MyRandom::Init();//乱数を読み込む
	Image::Init();//画像を読み込む
	gm.bgm = std::make_shared<BGM_Object>();
	gm.game_object_manager_ = std::make_shared<GameObjectManager>();
	MyDraw::InitMyDraw();
#ifdef _DEBUG

	Sound::Init();//デバグ時のみ音源のパスを確認する

#endif // _DEBUG
	Game::ChangeScene(m_title);
}

void Game::Update()
{
	if (gm.bgm != nullptr)	gm.bgm->Update();
	Input::Update();
	scenes->Update();//読み込まれるシーンの毎秒60回更新
	for (const auto& se : gm.soundEffects)
	{
		se->Update();
	}
	gm.EraseRemoveIf(gm.soundEffects, [](std::shared_ptr<SoundEffectObject>& ptr) {return ptr->isDead; });

}

void Game::Draw()
{
	scenes->Draw();//更新したシーンの状況を更新
}

void Game::ChangeScene(Scene* scene)//シーンを変えるときに、他所に呼ばれる
{
	scenes = scene;//呼ばれ先の次のシーンを定義
	scenes->Init();//読み込まれるシーンの初期化
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
