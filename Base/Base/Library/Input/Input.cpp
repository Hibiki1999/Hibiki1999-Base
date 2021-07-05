#include "Input.h"
#include "../Screen/Screen.h"

Input::Input(int pad)
{
	this->input_pad_ = pad;
}

Input::~Input() {}

void Input::Update()
{
	//�p�b�g��Ԏ擾
	GetJoypadXInputState(input_pad_, &input_);
	//�O��t���[���̃p�b�g��ԓo�^
	for (int i = 0; i < 16; i++) {
		pad_previous_state_[i] = pad_current_state_[i];
	}
	//���̃p�b�g��Ԏ擾
	for (int i = 0; i < 16; i++) {
		pad_current_state_[i] = input_.Buttons[i];
	}
	//�O��t���[���̃L�[�{�[�h��Ԃ�o�^
	for (int i = 0; i < 256; i++) {
		key_previous_state_[i] = key_current_state_[i];
	}
	//���̃L�[�{�[�h��Ԃ�o�^
	GetHitKeyStateAll(key_current_state_);
	//�}�E�X�̑O��t���[����Ԃ��擾
	mouse_previos_position_ = mouse_current_position_;
	//�}�E�X���̏�Ԃ��擾
	GetMousePoint(&get_mouse_x_, &get_mouse_y_);
	mouse_current_position_ = Vec2((float)get_mouse_x_, (float)get_mouse_y_);
	//�O��t���[���̃}�E�X���͏�Ԃ��L�^
	mouse_prev_state_ = mouse_current_state_;
	//���̃}�E�X���͂��擾
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
	//�p�b�g�A�L�[�{�[�g�A�}�E�X�ǂ��炩�����ꂽ��
	return GetPad(ActionName) || GetKey(ActionName) || GetMouse(ActionName);
}

bool Input::GetInputDown(std::string ActionName)
{
	//�p�b�g�A�L�[�{�[�g�A�}�E�X�ǂ��炩�����ꂽ��
	return GetPadDown(ActionName) || GetKeyDown(ActionName) || GetMouseDown(ActionName);
}

bool Input::GetInputUp(std::string ActionName)
{
	//�p�b�g�A�L�[�{�[�g�A�}�E�X�ǂ��炩�����ꂽ��
	return GetPadUp(ActionName) || GetKeyUp(ActionName) || GetMouseUp(ActionName);
}

bool Input::GetPad(int buttonID)
{
	//�p�b�g�̍��̏�Ԃ�����
	return pad_current_state_[buttonID];
}

bool Input::GetPad(std::string ActionName)
{
	//�p�b�g�p�ɖ��O�ɓo�^����Ă���{�^����T��
	std::vector<int> tempVec = InputIdFromList(ActionName, Pad);
	//�������{�^���̏�Ԃ�����
	for (auto id : tempVec) {
		//�����ꂽ��Ԃ��m�肳�ꂽ��true�ԋp
		if (GetPad(id)) {
			return GetPad(id);
		}
	}
	//��������Ԍ�����Ȃ�������False�ԋp
	return false;
}

bool Input::GetPadDown(int buttonID)
{
	//�p�b�g����1�����đO��0�̏ꍇ��True�ŕԋp�������̂ŁA 1 AND (NOT)0 = 1�̌`�Ōv�Z
	return pad_current_state_[buttonID] & ~pad_previous_state_[buttonID];
}

bool Input::GetPadDown(std::string ActionName)
{
	//�p�b�g�p�ɖ��O�ɓo�^����Ă���{�^����T��
	std::vector<int> tempVec = InputIdFromList(ActionName, Pad);
	//�������{�^���̏�Ԃ�����
	for (auto id : tempVec) {
		//�����ꂽ��Ԃ��m�肳�ꂽ��true�ԋp
		if (GetPadDown(id)) {
			return GetPadDown(id);
		}
	}
	//��������Ԍ�����Ȃ�������False�ԋp
	return false;
}

bool Input::GetPadUp(int buttonID)
{
	//�p�b�g����0�����đO��1�̏ꍇ��True�ŕԋp�������̂ŁA 1 AND (NOT)0 = 1�̌`�Ōv�Z
	return pad_previous_state_[buttonID] & ~pad_current_state_[buttonID];
}

bool Input::GetPadUp(std::string ActionName)
{
	//�p�b�g�p�ɖ��O�ɓo�^����Ă���{�^����T��
	std::vector<int> tempVec = InputIdFromList(ActionName, Pad);
	//�������{�^���̏�Ԃ�����
	for (auto id : tempVec) {
		//�����ꂽ��Ԃ��m�肳�ꂽ��true�ԋp
		if (GetPadUp(id)) {
			return GetPadUp(id);
		}
	}
	//��������Ԍ�����Ȃ�������False�ԋp
	return false;
}

Vec2 Input::GetPadLStick()
{
	//�p�b�g��L�X�e�B�b�N�̒l��0~1�ɂ��ĕԋp
	Vec2 tempVec = Vec2((float)input_.ThumbLX / 32767.0f, (float)input_.ThumbLY / 32767.0f);
	return tempVec;
}

Vec2 Input::GetPadRStick()
{
	//�p�b�g��R�X�e�B�b�N�̒l��0~1�ɂ��ĕԋp
	Vec2 tempVec = Vec2((float)input_.ThumbRX / 32767.0f, (float)input_.ThumbRY / 32767.0f);
	return tempVec;
}

float Input::GetPadLTrigger()
{
	//�p�b�g��L�g���K�[�̒l��0~1�ɂ��ĕԋp
	return (float)input_.LeftTrigger / 255.0f;
}

float Input::GetPadRTrigger()
{
	//�p�b�g��R�g���K�[�̒l��0~1�ɂ��ĕԋp
	return (float)input_.RightTrigger / 255.0f;
}

bool Input::GetKey(int keyId)
{
	//�L�[�{�[�h���̏�Ԃ�����
	return key_current_state_[keyId];
}

bool Input::GetKey(std::string ActionName)
{
	//�p�b�g�p�ɖ��O�ɓo�^����Ă���{�^����T��
	std::vector<int> tempVec = InputIdFromList(ActionName, KeyBoard);
	//�������{�^���̏�Ԃ�����
	for (auto id : tempVec) {
		//�����ꂽ��Ԃ��m�肳�ꂽ��true�ԋp
		if (GetKey(id)) {
			return GetKey(id);
		}
	}
	//��������Ԍ�����Ȃ�������False�ԋp
	return false;
}

bool Input::GetKeyDown(int keyId)
{
	//�L�[����1�����đO��0�̏ꍇ��True�ŕԋp�������̂ŁA 1 AND (NOT)0 = 1�̌`�Ōv�Z
	return key_current_state_[keyId] & ~key_previous_state_[keyId];
}

bool Input::GetKeyDown(std::string ActionName)
{
	//�p�b�g�p�ɖ��O�ɓo�^����Ă���{�^����T��
	std::vector<int> tempVec = InputIdFromList(ActionName, KeyBoard);
	//�������{�^���̏�Ԃ�����
	for (auto id : tempVec) {
		//�����ꂽ��Ԃ��m�肳�ꂽ��true�ԋp
		if (GetKeyDown(id)) {
			return GetKeyDown(id);
		}
	}
	//��������Ԍ�����Ȃ�������False�ԋp
	return false;
}

bool Input::GetKeyUp(int keyId)
{
	//�L�[����0�����đO��1�̏ꍇ��True�ŕԋp�������̂ŁA 1 AND (NOT)0 = 1�̌`�Ōv�Z
	return key_previous_state_[keyId] & ~key_current_state_[keyId];
}

bool Input::GetKeyUp(std::string ActionName)
{
	//�p�b�g�p�ɖ��O�ɓo�^����Ă���{�^����T��
	std::vector<int> tempVec = InputIdFromList(ActionName, KeyBoard);
	//�������{�^���̏�Ԃ�����
	for (auto id : tempVec) {
		//�����ꂽ��Ԃ��m�肳�ꂽ��true�ԋp
		if (GetKeyUp(id)) {
			return GetKeyUp(id);
		}
	}
	//��������Ԍ�����Ȃ�������False�ԋp
	return false;
}

bool Input::IsMouseMoving(Vec2* velo)
{
	Vec2 tempVec = mouse_current_position_ - mouse_previos_position_;
	tempVec.y = -tempVec.y;
	*velo = tempVec;
	//���̈ʒu�ƑO�̈ʒu���������True�ԋp
	return mouse_current_position_ != mouse_previos_position_;
}

bool Input::GetMouse(int button)
{
	//��������True�Ԃ�
	return(mouse_current_state_ & button);
}

bool Input::GetMouse(std::string ActionName)
{
	//�p�b�g�p�ɖ��O�ɓo�^����Ă���{�^����T��
	std::vector<int> tempVec = InputIdFromList(ActionName, Mouse);
	//�������{�^���̏�Ԃ�����
	for (auto id : tempVec) {
		//�����ꂽ��Ԃ��m�肳�ꂽ��true�ԋp
		if (GetMouse(id)) {
			return GetMouse(id);
		}
	}
	//��������Ԍ�����Ȃ�������False�ԋp
	return false;
}

bool Input::GetMouseDown(int button)
{
	//�����u��True�Ԃ�
	return((mouse_current_state_ & button) & ~(mouse_prev_state_ & button)) != 0;
}

bool Input::GetMouseDown(std::string ActionName)
{
	//�p�b�g�p�ɖ��O�ɓo�^����Ă���{�^����T��
	std::vector<int> tempVec = InputIdFromList(ActionName, Mouse);
	//�������{�^���̏�Ԃ�����
	for (auto id : tempVec) {
		//�����ꂽ��Ԃ��m�肳�ꂽ��true�ԋp
		if (GetMouseDown(id)) {
			return GetMouseDown(id);
		}
	}
	//��������Ԍ�����Ȃ�������False�ԋp
	return false;
}

bool Input::GetMouseUp(int button)
{
	//�����u��True�Ԃ�
	return((mouse_prev_state_ & button) & ~(mouse_current_state_ & button)) != 0;
}

bool Input::GetMouseUp(std::string ActionName)
{
	//�p�b�g�p�ɖ��O�ɓo�^����Ă���{�^����T��
	std::vector<int> tempVec = InputIdFromList(ActionName, Mouse);
	//�������{�^���̏�Ԃ�����
	for (auto id : tempVec) {
		//�����ꂽ��Ԃ��m�肳�ꂽ��true�ԋp
		if (GetMouseUp(id)) {
			return GetMouseUp(id);
		}
	}
	//��������Ԍ�����Ȃ�������False�ԋp
	return false;
}

Vec2 Input::GetMousePosition()
{
	//���̃}�E�X�̈ʒu��ԋp
	return mouse_current_position_;
}

void Input::RegisterButton(std::string action, int buttonId, int inputType)
{
	//�ꎞ�̃��X�g���쐬
	std::vector<std::string> tempvec;
	//�o�^�������A�N�V�����̖��O�ƑΉ�����{�^���ƃC���v�b�g�̎�ނ�o�^
	tempvec.push_back(action);
	tempvec.push_back(std::to_string(buttonId));
	tempvec.push_back(std::to_string(inputType));
	//�ꎞ���X�g�ɓo�^�����f�[�^�����C���̓o�^���X�g�ɓ����
	buttonName.push_back(tempvec);
	//�ꎞ�̃��X�g���N���A����
	tempvec.clear();
}

std::vector<int> Input::InputIdFromList(std::string action, int inputType)
{
	//�ꎞ���X�g���쐬
	std::vector<int> tempVec;
	for (int i = 0; i < buttonName.size(); i++) {
		//�w�肳�ꂽ�A�N�V����������������
		if (buttonName[i][ActionName] == action &&
			//�C���v�b�g�̎�ނ�������������
			std::stoi(buttonName[i][InputType]) == inputType) {
			//�ꎞ���X�g�Ƀ{�^��ID��o�^
			tempVec.push_back(std::stoi(buttonName[i][InputID]));
		}
	}
	//�ꎞ���X�g��ԋp
	return tempVec;
}
