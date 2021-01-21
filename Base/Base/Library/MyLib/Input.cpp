#include "Input.h"

int Input::prevState{ 0 }; // 1フレーム前の状態
int Input::currentState{ 0 }; // 現在の状態#include "Input.h"

void Input::Init()
{
	prevState = 0;
	currentState = 0;
}

// 最新の入力状況に更新する処理。
// 毎フレームの最初に（ゲームの処理より先に）呼んでください。
void Input::Update()
{
	prevState = currentState;

	currentState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
}

// ボタンが押されているか？
bool Input::GetButton(int buttonId)
{
	// 今ボタンが押されているかどうかを返却
	return (currentState & buttonId) != 0;
}

// ボタンが押された瞬間か？
bool Input::GetButtonDown(int buttonId)
{
	// 今は押されていて、かつ1フレーム前は押されていない場合はtrueを返却
	return ((currentState & buttonId) & ~(prevState & buttonId)) != 0;
}

// ボタンが離された瞬間か？
bool Input::GetButtonUp(int buttonId)
{
	// 1フレーム前は押されていて、かつ今は押されている場合はtrueを返却
	return ((prevState & buttonId) & ~(currentState & buttonId)) != 0;
}