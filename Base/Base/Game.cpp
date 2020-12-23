#include "Game.h"
#include "Scene/Child/Title/Title.h"
#include "Scene/Child/Playing/Playing.h"
#include "Scene/Child/Ending/Ending.h"

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
	Image::Init();//画像を読み込む
	Game::ChangeScene(m_title);
	
}

void Game::Update()
{
	scenes->Update();//読み込まれるシーンの毎秒60回更新
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
