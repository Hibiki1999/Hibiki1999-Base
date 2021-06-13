#ifndef INPUT_H_
#define INPUT_H_

#include <DxLib.h>
#include <unordered_map>//辞書配列

enum class Pad
{
	All = -2, // すべてのうちどれか1つでも押されたとき
	None = -1,
	One,
	Two,
	Three,
	Four,
	NUM,
};

// 入力クラス
class Input
{
public:
	
	// 初期化。最初に1回だけ呼んでください。
	static void Init();

	//使いたいボタンを登録
	static void RegisterButton(std::string action,int button);

	// 最新の入力状況に更新する処理。
	// 毎フレームの最初に（ゲームの処理より先に）呼んでください。
	static void Update();

	// ボタンが押されているか？
	static bool GetButton(Pad pad, std::string action);

	// ボタンが押された瞬間か？
	static bool GetButtonDown(Pad pad, std::string action);

	// ボタンが離された瞬間か？
	static bool GetButtonUp(Pad pad, std::string action);

	////右スティック動いいてるか
	//static bool IsRStickMoving(Pad pad);
	//
	////マウスの座標を記録
	//static int mouseX, mouseY;
	//static int prevMouseX, prevMouseY;
	//
	////マウス動いいてるか
	//static bool IsMouseMoving();
	//
	////マウス前一フレームの入力と今のフレームの入力を取得
	//static int prevMouseInput;
	//static int mouseInput;

	//static bool GetMouse(int button);//マウス押されてる状態

	//static bool GetMouseDown(int button);//マウス押される瞬間

	//static bool GetMouseUp(int button);//マウス放す瞬間

private:
	// ゲームパッドのナンバー
	static XINPUT_STATE stickInput[4];

	static int prevStates[(int)Pad::NUM]; // 1フレーム前の状態
	static int currentStates[(int)Pad::NUM]; // 現在の状態

	static std::unordered_map<int, int> padDic;

	static std::vector<std::vector<std::string>> buttonName;

	static void InitPadDictionary();//辞書配列の初期化

	static bool isCurrentPressed(Pad pad,std::string action);
	static bool isPreviousPressed(Pad pad,std::string action);
};

#endif
