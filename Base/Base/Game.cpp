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
	||使えるキーボードボタン											 ||
	||KEY_INPUT_A								// Ａキー				 ||
	||キーボード関数が多いため、直接KEY_INPUT_AにF12でライブラリにて参考 ||
	||===================================================================||
	||使えるマウスボタン                                                 ||
	||#define MOUSE_INPUT_LEFT				// マウス左ボタン			 ||
	||#define MOUSE_INPUT_RIGHT				// マウス右ボタン			 ||
	||#define MOUSE_INPUT_MIDDLE			// マウス中央ボタン			 ||
	||#define MOUSE_INPUT_4					// マウス４ボタン			 ||
	||#define MOUSE_INPUT_5					// マウス５ボタン			 ||
	||#define MOUSE_INPUT_6					// マウス６ボタン			 ||
	||#define MOUSE_INPUT_7					// マウス７ボタン			 ||
	||#define MOUSE_INPUT_8					// マウス８ボタン			 ||
	||===================================================================||
	*
	*/
	gm.input->RegisterButton("Forward", KEY_INPUT_W, InputType::KeyBoard);
	gm.input->RegisterButton("Backward", KEY_INPUT_S, InputType::KeyBoard);
	gm.input->RegisterButton("ToLeft", KEY_INPUT_A, InputType::KeyBoard);
	gm.input->RegisterButton("ToRight", KEY_INPUT_D, InputType::KeyBoard);
	gm.input->RegisterButton("Jump", KEY_INPUT_SPACE, InputType::KeyBoard);
	gm.input->RegisterButton("Forward", XINPUT_BUTTON_DPAD_UP, InputType::Pad);
	gm.input->RegisterButton("Backward", XINPUT_BUTTON_DPAD_DOWN, InputType::Pad);
	gm.input->RegisterButton("ToLeft", XINPUT_BUTTON_DPAD_LEFT, InputType::Pad);
	gm.input->RegisterButton("ToRight", XINPUT_BUTTON_DPAD_RIGHT, InputType::Pad);
	gm.input->RegisterButton("Jump", XINPUT_BUTTON_A, InputType::Pad);

}
/*

KEY_INPUT_BACK	// バックスペースキー
KEY_INPUT_TAB	// タブキー
KEY_INPUT_RETURN	// エンターキー

KEY_INPUT_LSHIFT	// 左シフトキー
KEY_INPUT_RSHIFT	// 右シフトキー
KEY_INPUT_LCONTROL	// 左コントロールキー
KEY_INPUT_RCONTROL	// 右コントロールキー
KEY_INPUT_ESCAPE	// エスケープキー
KEY_INPUT_SPACE	// スペースキー
KEY_INPUT_PGUP	// ＰａｇｅＵＰキー
KEY_INPUT_PGDN	// ＰａｇｅＤｏｗｎキー
KEY_INPUT_END	// エンドキー
KEY_INPUT_HOME	// ホームキー
KEY_INPUT_LEFT	// 左キー
KEY_INPUT_UP	// 上キー
KEY_INPUT_RIGHT	// 右キー
KEY_INPUT_DOWN	// 下キー
KEY_INPUT_INSERT	// インサートキー
KEY_INPUT_DELETE	// デリートキー

KEY_INPUT_MINUS	// －キー
KEY_INPUT_YEN	// ￥キー
KEY_INPUT_PREVTRACK	// ＾キー
KEY_INPUT_PERIOD	// ．キー
KEY_INPUT_SLASH	// ／キー
KEY_INPUT_LALT	// 左ＡＬＴキー
KEY_INPUT_RALT	// 右ＡＬＴキー
KEY_INPUT_SCROLL	// ScrollLockキー
KEY_INPUT_SEMICOLON	// ；キー
KEY_INPUT_COLON	// ：キー
KEY_INPUT_LBRACKET	// ［キー
KEY_INPUT_RBRACKET	// ］キー
KEY_INPUT_AT	// ＠キー
KEY_INPUT_BACKSLASH	// ＼キー
KEY_INPUT_COMMA	// ，キー
KEY_INPUT_CAPSLOCK	// CaspLockキー
KEY_INPUT_PAUSE	// PauseBreakキー

KEY_INPUT_NUMPAD0	// テンキー０
KEY_INPUT_NUMPAD1	// テンキー１
KEY_INPUT_NUMPAD2	// テンキー２
KEY_INPUT_NUMPAD3	// テンキー３
KEY_INPUT_NUMPAD4	// テンキー４
KEY_INPUT_NUMPAD5	// テンキー５
KEY_INPUT_NUMPAD6	// テンキー６
KEY_INPUT_NUMPAD7	// テンキー７
KEY_INPUT_NUMPAD8	// テンキー８
KEY_INPUT_NUMPAD9	// テンキー９
KEY_INPUT_MULTIPLY	// テンキー＊キー
KEY_INPUT_ADD	// テンキー＋キー
KEY_INPUT_SUBTRACT	// テンキー－キー
KEY_INPUT_DECIMAL	// テンキー．キー
KEY_INPUT_DIVIDE	// テンキー／キー
KEY_INPUT_NUMPADENTER	// テンキーのエンターキー

KEY_INPUT_F1	// Ｆ１キー
KEY_INPUT_F2	// Ｆ２キー
KEY_INPUT_F3	// Ｆ３キー
KEY_INPUT_F4	// Ｆ４キー
KEY_INPUT_F5	// Ｆ５キー
KEY_INPUT_F6	// Ｆ６キー
KEY_INPUT_F7	// Ｆ７キー
KEY_INPUT_F8	// Ｆ８キー
KEY_INPUT_F9	// Ｆ９キー
KEY_INPUT_F10	// Ｆ１０キー
KEY_INPUT_F11	// Ｆ１１キー
KEY_INPUT_F12	// Ｆ１２キー

KEY_INPUT_A	// Ａキー
KEY_INPUT_B	// Ｂキー
KEY_INPUT_C	// Ｃキー
KEY_INPUT_D	// Ｄキー
KEY_INPUT_E	// Ｅキー
KEY_INPUT_F	// Ｆキー
KEY_INPUT_G	// Ｇキー
KEY_INPUT_H	// Ｈキー
KEY_INPUT_I	// Ｉキー
KEY_INPUT_J	// Ｊキー
KEY_INPUT_K	// Ｋキー
KEY_INPUT_L	// Ｌキー
KEY_INPUT_M	// Ｍキー
KEY_INPUT_N	// Ｎキー
KEY_INPUT_O	// Ｏキー
KEY_INPUT_P	// Ｐキー
KEY_INPUT_Q	// Ｑキー
KEY_INPUT_R	// Ｒキー
KEY_INPUT_S	// Ｓキー
KEY_INPUT_T	// Ｔキー
KEY_INPUT_U	// Ｕキー
KEY_INPUT_V	// Ｖキー
KEY_INPUT_W	// Ｗキー
KEY_INPUT_X	// Ｘキー
KEY_INPUT_Y	// Ｙキー
KEY_INPUT_Z	// Ｚキー
KEY_INPUT_0	// ０キー
KEY_INPUT_1	// １キー
KEY_INPUT_2	// ２キー
KEY_INPUT_3	// ３キー
KEY_INPUT_4	// ４キー
KEY_INPUT_5	// ５キー
KEY_INPUT_6	// ６キー
KEY_INPUT_7	// ７キー
KEY_INPUT_8	// ８キー
KEY_INPUT_9	// ９キー
*/