#ifndef INPUT_H_
#define INPUT_H_

#include <DxLib.h>
#include <vector>
#include <string>

class Input
{
public:

	Input(int pad = DX_INPUT_PAD1);
	~Input();

	void Update();

	bool GetPad(int buttonID);
	bool GetPad(std::string ActionName);
	bool GetPadDown(int buttonID);
	bool GetPadDown(std::string ActionName);
	bool GetPadUp(int buttonID);
	bool GetPadUp(std::string ActionName);

	void RegisterButton(std::string action, int buttonId);

private:

	enum {
		ActionName,
		ButtonID,
	};

	std::vector<int> ButtonIdFromList(std::string action);

	int input_pad_ = 0;

	int previous_state_[16] = { 0 };
	int current_state_[16] = { 0 };

	std::vector<std::vector<std::string>> buttonName;

	XINPUT_STATE input_;
};

#endif
//
//enum class Pad
//{
//	All = -2, // すべてのうちどれか1つでも押されたとき
//	None = -1,
//	One,
//	Two,
//	Three,
//	Four,
//	NUM,
//};
//
//// 入力クラス
//class Input
//{
//public:
//
//	// 初期化。最初に1回だけ呼んでください。
//	static void Init();
//
//	//使いたいボタンを登録
//	static void RegisterButton(std::string action, int button);
//
//	// 最新の入力状況に更新する処理。
//	// 毎フレームの最初に（ゲームの処理より先に）呼んでください。
//	static void Update();
//
//	// ボタンが押されているか？
//	static bool GetButton(Pad pad, std::string action);
//	static bool GetButton(Pad pad, int button);
//
//	// ボタンが押された瞬間か？
//	static bool GetButtonDown(Pad pad, std::string action);
//	static bool GetButtonDown(Pad pad, int button);
//
//	// ボタンが離された瞬間か？
//	static bool GetButtonUp(Pad pad, std::string action);
//	static bool GetButtonUp(Pad pad, int button);
//
//	////右スティック動いいてるか
//	//static bool IsRStickMoving(Pad pad);
//	//
//	////マウスの座標を記録
//	//static int mouseX, mouseY;
//	//static int prevMouseX, prevMouseY;
//	//
//	////マウス動いいてるか
//	//static bool IsMouseMoving();
//	//
//	//マウス前一フレームの入力と今のフレームの入力を取得
//	//static int prevMouseInput;
//	//static int mouseInput;
//
//	//static bool GetMouse(int button);//マウス押されてる状態
//
//	//static bool GetMouseDown(int button);//マウス押される瞬間
//
//	//static bool GetMouseUp(int button);//マウス放す瞬間
//
//private:
//	enum
//	{
//		ButtonAction,
//		ButtonId,
//	};
//	// ゲームパッドのナンバー
//	static XINPUT_STATE stickInput[4];
//
//	static int prevStates[(int)Pad::NUM]; // 1フレーム前の状態
//	static int currentStates[(int)Pad::NUM]; // 現在の状態
//
//	static std::unordered_map<int, int> padDic;
//
//	static std::vector<std::vector<std::string>> buttonName;
//
//	static void InitPadDictionary();//辞書配列の初期化
//
//	static bool isCurrentPressed(Pad pad, std::string action);
//	static bool isPreviousPressed(Pad pad, std::string action);
//};
