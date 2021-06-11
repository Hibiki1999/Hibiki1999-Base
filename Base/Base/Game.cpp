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
