#include "Input.h"
#include "../Screen/Screen.h"

Input::Input(int pad)
{
	this->input_pad_ = pad;
}

Input::~Input() {}

void Input::Update()
{
	//パット状態取得
	GetJoypadXInputState(input_pad_, &input_);
	//前一フレームのパット状態登録
	for (int i = 0; i < 16; i++) {
		pad_previous_state_[i] = pad_current_state_[i];
	}
	//今のパット状態取得
	for (int i = 0; i < 16; i++) {
		pad_current_state_[i] = input_.Buttons[i];
	}
	//前一フレームのキーボード状態を登録
	for (int i = 0; i < 256; i++) {
		key_previous_state_[i] = key_current_state_[i];
	}
	//今のキーボード状態を登録
	GetHitKeyStateAll(key_current_state_);
	//マウスの前一フレーム状態を取得
	mouse_previos_position_ = mouse_current_position_;
	//マウス今の状態を取得
	GetMousePoint(&get_mouse_x_, &get_mouse_y_);
	mouse_current_position_ = Vec2((float)get_mouse_x_, (float)get_mouse_y_);
	//前一フレームのマウス入力状態を記録
	mouse_prev_state_ = mouse_current_state_;
	//今のマウス入力を取得
	mouse_current_state_ = GetMouseInput();
	if (mouse_current_position_.x < 0) {
		mouse_current_position_.x = Screen::Width;
		mouse_previos_position_ = mouse_current_position_;
	}
	else if (mouse_current_position_.x > Screen::Width) {
		mouse_current_position_.x = 0;
		mouse_previos_position_ = mouse_current_position_;
	}
	if (mouse_current_position_.y < 0) {
		mouse_current_position_.y = Screen::Height;
		mouse_previos_position_ = mouse_current_position_;
	}
	else if (mouse_current_position_.y > Screen::Height) {
		mouse_current_position_.y = 0;
		mouse_previos_position_ = mouse_current_position_;
	}
	SetMousePoint(mouse_current_position_.x, (int)mouse_current_position_.y);
}

bool Input::GetInput(std::string ActionName)
{
	//パット、キーボート、マウスどちらか押されたら
	return GetPad(ActionName) || GetKey(ActionName) || GetMouse(ActionName);
}

bool Input::GetInputDown(std::string ActionName)
{
	//パット、キーボート、マウスどちらか押されたら
	return GetPadDown(ActionName) || GetKeyDown(ActionName) || GetMouseDown(ActionName);
}

bool Input::GetInputUp(std::string ActionName)
{
	//パット、キーボート、マウスどちらか押されたら
	return GetPadUp(ActionName) || GetKeyUp(ActionName) || GetMouseUp(ActionName);
}

bool Input::GetPad(int buttonID)
{
	//パットの今の状態を検索
	return pad_current_state_[buttonID];
}

bool Input::GetPad(std::string ActionName)
{
	//パット用に名前に登録されているボタンを探す
	std::vector<int> tempVec = InputIdFromList(ActionName, Pad);
	//見つけたボタンの状態を検索
	for (auto id : tempVec) {
		//押された状態を確定されたらtrue返却
		if (GetPad(id)) {
			return GetPad(id);
		}
	}
	//押される状態見つからなかったらFalse返却
	return false;
}

bool Input::GetPadDown(int buttonID)
{
	//パット今が1そして前が0の場合はTrueで返却したいので、 1 AND (NOT)0 = 1の形で計算
	return pad_current_state_[buttonID] & ~pad_previous_state_[buttonID];
}

bool Input::GetPadDown(std::string ActionName)
{
	//パット用に名前に登録されているボタンを探す
	std::vector<int> tempVec = InputIdFromList(ActionName, Pad);
	//見つけたボタンの状態を検索
	for (auto id : tempVec) {
		//押された状態を確定されたらtrue返却
		if (GetPadDown(id)) {
			return GetPadDown(id);
		}
	}
	//押される状態見つからなかったらFalse返却
	return false;
}

bool Input::GetPadUp(int buttonID)
{
	//パット今が0そして前が1の場合はTrueで返却したいので、 1 AND (NOT)0 = 1の形で計算
	return pad_previous_state_[buttonID] & ~pad_current_state_[buttonID];
}

bool Input::GetPadUp(std::string ActionName)
{
	//パット用に名前に登録されているボタンを探す
	std::vector<int> tempVec = InputIdFromList(ActionName, Pad);
	//見つけたボタンの状態を検索
	for (auto id : tempVec) {
		//押された状態を確定されたらtrue返却
		if (GetPadUp(id)) {
			return GetPadUp(id);
		}
	}
	//押される状態見つからなかったらFalse返却
	return false;
}

Vec2 Input::GetPadLStick()
{
	//パットのLスティックの値を0~1にして返却
	Vec2 tempVec = Vec2((float)input_.ThumbLX / 32767.0f, (float)input_.ThumbLY / 32767.0f);
	return tempVec;
}

Vec2 Input::GetPadRStick()
{
	//パットのRスティックの値を0~1にして返却
	Vec2 tempVec = Vec2((float)input_.ThumbRX / 32767.0f, (float)input_.ThumbRY / 32767.0f);
	return tempVec;
}

float Input::GetPadLTrigger()
{
	//パットのLトリガーの値を0~1にして返却
	return (float)input_.LeftTrigger / 255.0f;
}

float Input::GetPadRTrigger()
{
	//パットのRトリガーの値を0~1にして返却
	return (float)input_.RightTrigger / 255.0f;
}

bool Input::GetKey(int keyId)
{
	//キーボード今の状態を検索
	return key_current_state_[keyId];
}

bool Input::GetKey(std::string ActionName)
{
	//パット用に名前に登録されているボタンを探す
	std::vector<int> tempVec = InputIdFromList(ActionName, KeyBoard);
	//見つけたボタンの状態を検索
	for (auto id : tempVec) {
		//押された状態を確定されたらtrue返却
		if (GetKey(id)) {
			return GetKey(id);
		}
	}
	//押される状態見つからなかったらFalse返却
	return false;
}

bool Input::GetKeyDown(int keyId)
{
	//キー今が1そして前が0の場合はTrueで返却したいので、 1 AND (NOT)0 = 1の形で計算
	return key_current_state_[keyId] & ~key_previous_state_[keyId];
}

bool Input::GetKeyDown(std::string ActionName)
{
	//パット用に名前に登録されているボタンを探す
	std::vector<int> tempVec = InputIdFromList(ActionName, KeyBoard);
	//見つけたボタンの状態を検索
	for (auto id : tempVec) {
		//押された状態を確定されたらtrue返却
		if (GetKeyDown(id)) {
			return GetKeyDown(id);
		}
	}
	//押される状態見つからなかったらFalse返却
	return false;
}

bool Input::GetKeyUp(int keyId)
{
	//キー今が0そして前が1の場合はTrueで返却したいので、 1 AND (NOT)0 = 1の形で計算
	return key_previous_state_[keyId] & ~key_current_state_[keyId];
}

bool Input::GetKeyUp(std::string ActionName)
{
	//パット用に名前に登録されているボタンを探す
	std::vector<int> tempVec = InputIdFromList(ActionName, KeyBoard);
	//見つけたボタンの状態を検索
	for (auto id : tempVec) {
		//押された状態を確定されたらtrue返却
		if (GetKeyUp(id)) {
			return GetKeyUp(id);
		}
	}
	//押される状態見つからなかったらFalse返却
	return false;
}

bool Input::IsMouseMoving(Vec2* velo)
{
	Vec2 tempVec = mouse_current_position_ - mouse_previos_position_;
	tempVec.y = -tempVec.y;
	*velo = tempVec;
	//今の位置と前の位置が違ったらTrue返却
	return mouse_current_position_ != mouse_previos_position_;
}

bool Input::GetMouse(int button)
{
	//押されるとTrue返す
	return(mouse_current_state_ & button);
}

bool Input::GetMouse(std::string ActionName)
{
	//パット用に名前に登録されているボタンを探す
	std::vector<int> tempVec = InputIdFromList(ActionName, Mouse);
	//見つけたボタンの状態を検索
	for (auto id : tempVec) {
		//押された状態を確定されたらtrue返却
		if (GetMouse(id)) {
			return GetMouse(id);
		}
	}
	//押される状態見つからなかったらFalse返却
	return false;
}

bool Input::GetMouseDown(int button)
{
	//押す瞬間True返す
	return((mouse_current_state_ & button) & ~(mouse_prev_state_ & button)) != 0;
}

bool Input::GetMouseDown(std::string ActionName)
{
	//パット用に名前に登録されているボタンを探す
	std::vector<int> tempVec = InputIdFromList(ActionName, Mouse);
	//見つけたボタンの状態を検索
	for (auto id : tempVec) {
		//押された状態を確定されたらtrue返却
		if (GetMouseDown(id)) {
			return GetMouseDown(id);
		}
	}
	//押される状態見つからなかったらFalse返却
	return false;
}

bool Input::GetMouseUp(int button)
{
	//放す瞬間True返す
	return((mouse_prev_state_ & button) & ~(mouse_current_state_ & button)) != 0;
}

bool Input::GetMouseUp(std::string ActionName)
{
	//パット用に名前に登録されているボタンを探す
	std::vector<int> tempVec = InputIdFromList(ActionName, Mouse);
	//見つけたボタンの状態を検索
	for (auto id : tempVec) {
		//押された状態を確定されたらtrue返却
		if (GetMouseUp(id)) {
			return GetMouseUp(id);
		}
	}
	//押される状態見つからなかったらFalse返却
	return false;
}

Vec2 Input::GetMousePosition()
{
	//今のマウスの位置を返却
	return mouse_current_position_;
}

void Input::RegisterButton(std::string action, int buttonId, int inputType)
{
	//一時のリストを作成
	std::vector<std::string> tempvec;
	//登録したいアクションの名前と対応するボタンとインプットの種類を登録
	tempvec.push_back(action);
	tempvec.push_back(std::to_string(buttonId));
	tempvec.push_back(std::to_string(inputType));
	//一時リストに登録したデータをメインの登録リストに入れる
	buttonName.push_back(tempvec);
	//一時のリストをクリアする
	tempvec.clear();
}

std::vector<int> Input::InputIdFromList(std::string action, int inputType)
{
	//一時リストを作成
	std::vector<int> tempVec;
	for (int i = 0; i < buttonName.size(); i++) {
		//指定されたアクション名が同じかつ
		if (buttonName[i][ActionName] == action &&
			//インプットの種類も同じだったら
			std::stoi(buttonName[i][InputType]) == inputType) {
			//一時リストにボタンIDを登録
			tempVec.push_back(std::stoi(buttonName[i][InputID]));
		}
	}
	//一時リストを返却
	return tempVec;
}
