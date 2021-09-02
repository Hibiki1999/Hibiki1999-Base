#ifndef INPUT_H_
#define INPUT_H_

#include <DxLib.h>
#include <vector>
#include <string>

#include "../Transform/Vec2/Vec2.h"

//ボタンを定義する時に使うインプットの種類、これ定義ちゃんと入れないとバグります
enum InputType {
	Pad,
	KeyBoard,
	Mouse,
};

class Input
{
public:
	//インプットを生成、padを変えれば4つのコンロトラ―まで対応できる。キーボードとマウス増やせないので注意！
	Input(int pad = DX_INPUT_PAD1);
	~Input();
	//インプットの状態を更新
	void Update();
	//定義したインプットの名前をキーボード、マウス、パットに関係なく使える
	bool GetInput(std::string ActionName);
	bool GetInputDown(std::string ActionName);
	bool GetInputUp(std::string ActionName);
	//パットの各種状態
	bool GetPad(int buttonID);
	bool GetPad(std::string ActionName);
	bool GetPadDown(int buttonID);
	bool GetPadDown(std::string ActionName);
	bool GetPadUp(int buttonID);
	bool GetPadUp(std::string ActionName);
	Vec2 GetPadLStick();
	Vec2 GetPadRStick();
	float GetPadLTrigger();
	float GetPadRTrigger();
	//キーボードの各種状態
	bool GetKey(int keyId);
	bool GetKey(std::string ActionName);
	bool GetKeyDown(int keyId);
	bool GetKeyDown(std::string ActionName);
	bool GetKeyUp(int keyId);
	bool GetKeyUp(std::string ActionName);
	//マウスの各種状態
	bool IsMouseMoving(Vec2 *velo);
	bool GetMouse(int button);
	bool GetMouse(std::string ActionName);
	bool GetMouseDown(int button);
	bool GetMouseDown(std::string ActionName);
	bool GetMouseUp(int button);
	bool GetMouseUp(std::string ActionName);
	Vec2 GetMousePosition();
	//ボタンをstringに定義し、簡単で切り替えたりする
	void RegisterButton(std::string action, int buttonId, int inputType);
	//マウスを画面ないに固定
	void KeepCursorInScreen();
	//マウスを表示するか？
	void IsShowCursor(bool b);
	//任意キー
	bool AnyKeyDown();

private:

	//定義登録用に
	enum {
		ActionName,
		InputID,
		InputType,
	};
	//vectorから登録したボタンを呼び出す
	std::vector<int> InputIdFromList(std::string action, int inputType);
	//今のパット
	int input_pad_ = 0;
	//今のパットの状態
	int pad_previous_state_[16] = { 0 };
	int pad_current_state_[16] = { 0 };
	//キーボートの状態
	char key_previous_state_[256] = { '0' };
	char key_current_state_[256] = { '0' };
	//マウス前一フレームの入力と今のフレームの入力を取得
	int mouse_prev_state_ = 0;
	int mouse_current_state_ = 0;
	//マウスの座標を記録
	Vec2 mouse_current_position_ = Vec2(0, 0);
	Vec2 mouse_previos_position_ = Vec2(0, 0);
	int get_mouse_x_, get_mouse_y_ = 0;
	//定義したボタンの名前はこちらで登録
	std::vector<std::vector<std::string>> buttonName;
	//パット機能を呼ぶ
	XINPUT_STATE input_;
};

#endif
