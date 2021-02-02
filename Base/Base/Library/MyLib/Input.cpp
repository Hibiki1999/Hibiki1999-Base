#include "Input.h"

int Input::prevStates[]; // 1フレーム前の状態
int Input::currentStates[]; // 現在の状態
int Input::mouseX{ 0 };
int Input::mouseY{ 0 };
int Input::prevMouseX{ 0 };
int Input::prevMouseY{ 0 };

XINPUT_STATE Input::input[4];

std::unordered_map<int, int> Input::padDic; // パッド番号からDXの定義への辞書

void Input::InitPadDictionary()
{
	// 辞書配列で対応関係の辞書を作成しておく
	padDic[(int)Pad::One] = DX_INPUT_KEY_PAD1;
	padDic[(int)Pad::Two] = DX_INPUT_PAD2;
	padDic[(int)Pad::Three] = DX_INPUT_PAD3;
	padDic[(int)Pad::Four] = DX_INPUT_PAD4;
}

void Input::Init()
{
	InitPadDictionary();// パッドの辞書配列の初期化

		// キー状態をゼロリセット
	for (int i = 0; i < (int)Pad::NUM; i++)
		prevStates[i] = currentStates[i] = 0;

}

// 最新の入力状況に更新する処理。
// 毎フレームの最初に（ゲームの処理より先に）呼んでください。
void Input::Update()
{
	for (int i = 0; i < (int)Pad::NUM; i++)
	{    // 現在の状態を一つ前の状態として保存してGetJoypad..
		prevStates[i] = currentStates[i];
		currentStates[i] = GetJoypadInputState(padDic[i]);
	}

	for (int i = 0; i < (int)Pad::NUM; i++)GetJoypadXInputState(padDic[i], &input[i]);

	prevMouseX = mouseX;
	prevMouseY = mouseY;
	GetMousePoint(&mouseX, &mouseY);//今のマウスの座標を取得
}

// ボタンが押されているか？
bool Input::GetButton(Pad pad, int buttonId)
{
	if (pad == Pad::None) return false; // Noneなら判別不要
	else if (pad == Pad::All) // All指定の時は全てのパッド
	{    // GetButtonの中でGetButtonを呼ぶ【再起呼出し】テクニック
		for (int i = 0; i < (int)Pad::NUM; i++)
			if (GetButton((Pad)i, buttonId))
				return true; //押されているPadを発見！
		return false; // 一つも押されていなかった
	}
	// 今ボタンが押されているかどうかを返却
	return (currentStates[(int)pad] & buttonId) != 0;
}

// ボタンが押された瞬間か？
bool Input::GetButtonDown(Pad pad, int buttonId)
{
	if (pad == Pad::None) return false; // Noneなら判別不要
	else if (pad == Pad::All) // All指定の時は全てのパッド
	{    // 再起呼出しテクニック
		for (int i = 0; i < (int)Pad::NUM; i++)
			if (GetButtonDown((Pad)i, buttonId))
				return true; //押されているPadを発見！
		return false; // 一つも押されていなかった
	}
	// 今は押されていて、かつ1フレーム前は押されていない場合はtrueを返却
	return ((currentStates[(int)pad] & buttonId) & ~(prevStates[(int)pad] & buttonId)) != 0;
}

// ボタンが離された瞬間か？
bool Input::GetButtonUp(Pad pad, int buttonId)
{
	if (pad == Pad::None) return false; // Noneなら判別不要
	else if (pad == Pad::All) // All指定の時は全てのパッド
	{    // 再起呼出しテクニック
		for (int i = 0; i < (int)Pad::NUM; i++)
			if (GetButtonUp((Pad)i, buttonId))
				return true; //押されているPadを発見！
		return false; // 一つも押されていなかった
	}
	// 1フレーム前は押されていて、かつ今は押されている場合はtrueを返却
	return ((prevStates[(int)pad] & buttonId) & ~(currentStates[(int)pad] & buttonId)) != 0;
}

bool Input::IsMouseMoving()
{
	return ((prevMouseX != mouseX) && (prevMouseY != mouseY));//動いてるならTrueを返す
}

bool Input::IsRStickMoving(Pad pad)
{
	return((input[(int)pad].ThumbRX != 0) && (input[(int)pad].ThumbRY != 0));//動いてるならTrueを返す
}