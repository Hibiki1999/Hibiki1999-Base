#include "Input.h"


Input::Input(int pad)
{
	this->input_pad_ = pad;
}

Input::~Input()
{
}

void Input::Update()
{
	GetJoypadXInputState(input_pad_, &input_);

	for (int i = 0; i < 16; i++) {
		previous_state_[i] = current_state_[i];
	}
	for (int i = 0; i < 16; i++) {
		current_state_[i] = input_.Buttons[i];
	}

}

bool Input::GetPad(int buttonID)
{
	return current_state_[buttonID];
}

bool Input::GetPad(std::string ActionName)
{
	std::vector<int> tempVec = ButtonIdFromList(ActionName);
	int isPressed = 0;
	for (auto id : tempVec) {
		isPressed |= current_state_[id];
	}
	return isPressed;
}

bool Input::GetPadDown(int buttonID)
{
	return current_state_[buttonID] & ~previous_state_[buttonID];
}

bool Input::GetPadDown(std::string ActionName)
{
	std::vector<int> tempVec = ButtonIdFromList(ActionName);
	int isPressed = 0;
	for (auto id : tempVec) {
		isPressed |= GetPadDown(id);
	}
	return isPressed;
}

bool Input::GetPadUp(int buttonID)
{
	return previous_state_[buttonID] & ~current_state_[buttonID];
}

bool Input::GetPadUp(std::string ActionName)
{
	std::vector<int> tempVec = ButtonIdFromList(ActionName);
	int isPressed = 0;
	for (auto id : tempVec) {
		isPressed |= GetPadUp(id);
	}
	return isPressed;
}

void Input::RegisterButton(std::string action, int buttonId)
{
	std::vector<std::string> tempvec;
	tempvec.push_back(action);
	tempvec.push_back(std::to_string(buttonId));
	buttonName.push_back(tempvec);
	tempvec.clear();
}

std::vector<int> Input::ButtonIdFromList(std::string action)
{
	std::vector<int> tempVec;
	for (int i = 0; i < buttonName.size(); i++) {
		if (buttonName[i][ActionName] == action) {
			tempVec.push_back(std::stoi(buttonName[i][ButtonID]));
		}
	}
	return tempVec;
}


//
//int Input::prevStates[]; // 1フレーム前の状態
//int Input::currentStates[]; // 現在の状態
////int Input::mouseX{ 0 };//今のマウスのX座標
////int Input::mouseY{ 0 };//今のマウスのY座標
////int Input::prevMouseX{ 0 };//一フレーム前のマウスX座標
////int Input::prevMouseY{ 0 };//一フレーム前のマウスY座標
////int Input::prevMouseInput{ 0 };//一フレーム前のマウス入力状態
////int Input::mouseInput{ 0 };//今のマウスの入力状態
//
//XINPUT_STATE Input::stickInput[4];//スティックを取得したの保存先
//
//std::unordered_map<int, int> Input::padDic; // パッド番号からDXの定義への辞書
//std::vector<std::vector<std::string>> Input::buttonName; // パッド番号からDXの定義への辞書
//
//void Input::InitPadDictionary()
//{
//	// 辞書配列で対応関係の辞書を作成しておく
//	padDic[(int)Pad::One] = DX_INPUT_KEY_PAD1;
//	padDic[(int)Pad::Two] = DX_INPUT_PAD2;
//	padDic[(int)Pad::Three] = DX_INPUT_PAD3;
//	padDic[(int)Pad::Four] = DX_INPUT_PAD4;
//}
//
//bool Input::isCurrentPressed(Pad pad, std::string action)
//{
//	std::vector<int> buttonId;
//	for (int i = 0; i < buttonName.size(); i++) {
//		if (buttonName[i][ButtonAction] == action) {
//			buttonId.push_back(std::stoi(buttonName[i][ButtonId]));
//		}
//	}
//	bool isInput = false;
//	for (auto bi : buttonId) {
//		if ((currentStates[(int)pad] & bi) != 0) {
//			isInput = true;
//		}
//	}
//	return isInput;
//}
//
//bool Input::isPreviousPressed(Pad pad, std::string action)
//{
//	std::vector<int> buttonId;
//	for (int i = 0; i < buttonName.size(); i++) {
//		if (buttonName[i][ButtonAction] == action) {
//			buttonId.push_back(std::stoi(buttonName[i][ButtonId]));
//		}
//	}
//	bool isInput = false;
//	for (auto bi : buttonId) {
//		if ((prevStates[(int)pad] & bi) != 0) {
//			isInput = true;
//		}
//	}
//	return isInput;
//}
//
//void Input::Init()
//{
//	InitPadDictionary();// パッドの辞書配列の初期化
//
//		// キー状態をゼロリセット
//	for (int i = 0; i < (int)Pad::NUM; i++)
//		prevStates[i] = currentStates[i] = 0;
//
//}
//
//void Input::RegisterButton(std::string action, int button)
//{
//	std::vector<std::string> tempvec;
//	tempvec.push_back(action);
//	tempvec.push_back(std::to_string(button));
//	buttonName.push_back(tempvec);
//	tempvec.clear();
//}
//
//// 最新の入力状況に更新する処理。
//// 毎フレームの最初に（ゲームの処理より先に）呼んでください。
//void Input::Update()
//{
//	for (int i = 0; i < (int)Pad::NUM; i++)
//	{    // 現在の状態を一つ前の状態として保存してGetJoypad..
//		prevStates[i] = currentStates[i];
//		currentStates[i] = GetJoypadInputState(padDic[i]);
//	}
//
//	for (int i = 0; i < (int)Pad::NUM; i++)
//		GetJoypadXInputState(padDic[i], &stickInput[i]);//パットのスティック状態を取得するための再読み込み
//
//	//prevMouseX = mouseX;
//	//prevMouseY = mouseY;//前一フレームのマウス座標を取得
//	//GetMousePoint(&mouseX, &mouseY);//今のマウスの座標を取得
//	//prevMouseInput = mouseInput;//前一フレームのマウス入力状態を記録
//	//mouseInput = GetMouseInput();//今のマウス入力を取得
//}
//
//// ボタンが押されているか？
//bool Input::GetButton(Pad pad, std::string action)
//{
//	if (pad == Pad::None) return false; // Noneなら判別不要
//	else if (pad == Pad::All) // All指定の時は全てのパッド
//	{    // GetButtonの中でGetButtonを呼ぶ【再起呼出し】テクニック
//		for (int i = 0; i < (int)Pad::NUM; i++)
//			if (GetButton((Pad)i, action))
//				return true; //押されているPadを発見！
//		return false; // 一つも押されていなかった
//	}
//	// 今ボタンが押されているかどうかを返却
//
//	return isCurrentPressed(pad, action);
//}
//
//// ボタンが押されているか？
//bool Input::GetButton(Pad pad, int buttonId)
//{
//	if (pad == Pad::None) return false; // Noneなら判別不要
//	else if (pad == Pad::All) // All指定の時は全てのパッド
//	{    // GetButtonの中でGetButtonを呼ぶ【再起呼出し】テクニック
//		for (int i = 0; i < (int)Pad::NUM; i++)
//			if (GetButton((Pad)i, buttonId))
//				return true; //押されているPadを発見！
//		return false; // 一つも押されていなかった
//	}
//	// 今ボタンが押されているかどうかを返却
//	return (currentStates[(int)pad] & buttonId) != 0;
//}
//
//
//// ボタンが押された瞬間か？
//bool Input::GetButtonDown(Pad pad, std::string action)
//{
//	if (pad == Pad::None) return false; // Noneなら判別不要
//	else if (pad == Pad::All) // All指定の時は全てのパッド
//	{    // 再起呼出しテクニック
//		for (int i = 0; i < (int)Pad::NUM; i++)
//			if (GetButtonDown((Pad)i, action))
//				return true; //押されているPadを発見！
//		return false; // 一つも押されていなかった
//	}
//	// 今は押されていて、かつ1フレーム前は押されていない場合はtrueを返却
//	return ((isCurrentPressed(pad, action)) & !(isPreviousPressed(pad, action)));
//}
//
//// ボタンが押された瞬間か？
//bool Input::GetButtonDown(Pad pad, int buttonId)
//{
//	if (pad == Pad::None) return false; // Noneなら判別不要
//	else if (pad == Pad::All) // All指定の時は全てのパッド
//	{    // 再起呼出しテクニック
//		for (int i = 0; i < (int)Pad::NUM; i++)
//			if (GetButtonDown((Pad)i, buttonId))
//				return true; //押されているPadを発見！
//		return false; // 一つも押されていなかった
//	}
//	// 今は押されていて、かつ1フレーム前は押されていない場合はtrueを返却
//	return ((currentStates[(int)pad] & buttonId) & ~(prevStates[(int)pad] & buttonId)) != 0;
//}
//
//// ボタンが離された瞬間か？
//bool Input::GetButtonUp(Pad pad, std::string action)
//{
//	if (pad == Pad::None) return false; // Noneなら判別不要
//	else if (pad == Pad::All) // All指定の時は全てのパッド
//	{    // 再起呼出しテクニック
//		for (int i = 0; i < (int)Pad::NUM; i++)
//			if (GetButtonUp((Pad)i, action))
//				return true; //押されているPadを発見！
//		return false; // 一つも押されていなかった
//	}
//	// 1フレーム前は押されていて、かつ今は押されている場合はtrueを返却
//	return ((isPreviousPressed(pad, action)) & !(isCurrentPressed(pad, action)));
//}
//
//// ボタンが離された瞬間か？
//bool Input::GetButtonUp(Pad pad, int buttonId)
//{
//	if (pad == Pad::None) return false; // Noneなら判別不要
//	else if (pad == Pad::All) // All指定の時は全てのパッド
//	{    // 再起呼出しテクニック
//		for (int i = 0; i < (int)Pad::NUM; i++)
//			if (GetButtonUp((Pad)i, buttonId))
//				return true; //押されているPadを発見！
//		return false; // 一つも押されていなかった
//	}
//	// 1フレーム前は押されていて、かつ今は押されている場合はtrueを返却
//	return ((prevStates[(int)pad] & buttonId) & ~(currentStates[(int)pad] & buttonId)) != 0;
//}
//
////
////bool Input::IsMouseMoving()
////{
////	return ((prevMouseX != mouseX) && (prevMouseY != mouseY));//動いてるならTrueを返す
////}
////
////bool Input::IsRStickMoving(Pad pad)
////{
////	return((stickInput[(int)pad].ThumbRX != 0) && (stickInput[(int)pad].ThumbRY != 0));//動いてるならTrueを返す
////}
////
////bool Input::GetMouse(int button)
////{
////	return(mouseInput & button);//押されるとTrue返す
////}
////
////bool Input::GetMouseDown(int button)
////{
////	return((mouseInput & button) & ~(prevMouseInput & button)) != 0;//押す瞬間True返す
////}
////
////bool Input::GetMouseUp(int button)
////{
////	return((prevMouseInput & button) & ~(mouseInput & button)) != 0;//放す瞬間True返す
////}

