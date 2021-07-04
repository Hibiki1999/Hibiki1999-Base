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
//int Input::prevStates[]; // 1�t���[���O�̏��
//int Input::currentStates[]; // ���݂̏��
////int Input::mouseX{ 0 };//���̃}�E�X��X���W
////int Input::mouseY{ 0 };//���̃}�E�X��Y���W
////int Input::prevMouseX{ 0 };//��t���[���O�̃}�E�XX���W
////int Input::prevMouseY{ 0 };//��t���[���O�̃}�E�XY���W
////int Input::prevMouseInput{ 0 };//��t���[���O�̃}�E�X���͏��
////int Input::mouseInput{ 0 };//���̃}�E�X�̓��͏��
//
//XINPUT_STATE Input::stickInput[4];//�X�e�B�b�N���擾�����̕ۑ���
//
//std::unordered_map<int, int> Input::padDic; // �p�b�h�ԍ�����DX�̒�`�ւ̎���
//std::vector<std::vector<std::string>> Input::buttonName; // �p�b�h�ԍ�����DX�̒�`�ւ̎���
//
//void Input::InitPadDictionary()
//{
//	// �����z��őΉ��֌W�̎������쐬���Ă���
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
//	InitPadDictionary();// �p�b�h�̎����z��̏�����
//
//		// �L�[��Ԃ��[�����Z�b�g
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
//// �ŐV�̓��͏󋵂ɍX�V���鏈���B
//// ���t���[���̍ŏ��Ɂi�Q�[���̏�������Ɂj�Ă�ł��������B
//void Input::Update()
//{
//	for (int i = 0; i < (int)Pad::NUM; i++)
//	{    // ���݂̏�Ԃ���O�̏�ԂƂ��ĕۑ�����GetJoypad..
//		prevStates[i] = currentStates[i];
//		currentStates[i] = GetJoypadInputState(padDic[i]);
//	}
//
//	for (int i = 0; i < (int)Pad::NUM; i++)
//		GetJoypadXInputState(padDic[i], &stickInput[i]);//�p�b�g�̃X�e�B�b�N��Ԃ��擾���邽�߂̍ēǂݍ���
//
//	//prevMouseX = mouseX;
//	//prevMouseY = mouseY;//�O��t���[���̃}�E�X���W���擾
//	//GetMousePoint(&mouseX, &mouseY);//���̃}�E�X�̍��W���擾
//	//prevMouseInput = mouseInput;//�O��t���[���̃}�E�X���͏�Ԃ��L�^
//	//mouseInput = GetMouseInput();//���̃}�E�X���͂��擾
//}
//
//// �{�^����������Ă��邩�H
//bool Input::GetButton(Pad pad, std::string action)
//{
//	if (pad == Pad::None) return false; // None�Ȃ画�ʕs�v
//	else if (pad == Pad::All) // All�w��̎��͑S�Ẵp�b�h
//	{    // GetButton�̒���GetButton���Ăԁy�ċN�ďo���z�e�N�j�b�N
//		for (int i = 0; i < (int)Pad::NUM; i++)
//			if (GetButton((Pad)i, action))
//				return true; //������Ă���Pad�𔭌��I
//		return false; // ���������Ă��Ȃ�����
//	}
//	// ���{�^����������Ă��邩�ǂ�����ԋp
//
//	return isCurrentPressed(pad, action);
//}
//
//// �{�^����������Ă��邩�H
//bool Input::GetButton(Pad pad, int buttonId)
//{
//	if (pad == Pad::None) return false; // None�Ȃ画�ʕs�v
//	else if (pad == Pad::All) // All�w��̎��͑S�Ẵp�b�h
//	{    // GetButton�̒���GetButton���Ăԁy�ċN�ďo���z�e�N�j�b�N
//		for (int i = 0; i < (int)Pad::NUM; i++)
//			if (GetButton((Pad)i, buttonId))
//				return true; //������Ă���Pad�𔭌��I
//		return false; // ���������Ă��Ȃ�����
//	}
//	// ���{�^����������Ă��邩�ǂ�����ԋp
//	return (currentStates[(int)pad] & buttonId) != 0;
//}
//
//
//// �{�^���������ꂽ�u�Ԃ��H
//bool Input::GetButtonDown(Pad pad, std::string action)
//{
//	if (pad == Pad::None) return false; // None�Ȃ画�ʕs�v
//	else if (pad == Pad::All) // All�w��̎��͑S�Ẵp�b�h
//	{    // �ċN�ďo���e�N�j�b�N
//		for (int i = 0; i < (int)Pad::NUM; i++)
//			if (GetButtonDown((Pad)i, action))
//				return true; //������Ă���Pad�𔭌��I
//		return false; // ���������Ă��Ȃ�����
//	}
//	// ���͉�����Ă��āA����1�t���[���O�͉�����Ă��Ȃ��ꍇ��true��ԋp
//	return ((isCurrentPressed(pad, action)) & !(isPreviousPressed(pad, action)));
//}
//
//// �{�^���������ꂽ�u�Ԃ��H
//bool Input::GetButtonDown(Pad pad, int buttonId)
//{
//	if (pad == Pad::None) return false; // None�Ȃ画�ʕs�v
//	else if (pad == Pad::All) // All�w��̎��͑S�Ẵp�b�h
//	{    // �ċN�ďo���e�N�j�b�N
//		for (int i = 0; i < (int)Pad::NUM; i++)
//			if (GetButtonDown((Pad)i, buttonId))
//				return true; //������Ă���Pad�𔭌��I
//		return false; // ���������Ă��Ȃ�����
//	}
//	// ���͉�����Ă��āA����1�t���[���O�͉�����Ă��Ȃ��ꍇ��true��ԋp
//	return ((currentStates[(int)pad] & buttonId) & ~(prevStates[(int)pad] & buttonId)) != 0;
//}
//
//// �{�^���������ꂽ�u�Ԃ��H
//bool Input::GetButtonUp(Pad pad, std::string action)
//{
//	if (pad == Pad::None) return false; // None�Ȃ画�ʕs�v
//	else if (pad == Pad::All) // All�w��̎��͑S�Ẵp�b�h
//	{    // �ċN�ďo���e�N�j�b�N
//		for (int i = 0; i < (int)Pad::NUM; i++)
//			if (GetButtonUp((Pad)i, action))
//				return true; //������Ă���Pad�𔭌��I
//		return false; // ���������Ă��Ȃ�����
//	}
//	// 1�t���[���O�͉�����Ă��āA�����͉�����Ă���ꍇ��true��ԋp
//	return ((isPreviousPressed(pad, action)) & !(isCurrentPressed(pad, action)));
//}
//
//// �{�^���������ꂽ�u�Ԃ��H
//bool Input::GetButtonUp(Pad pad, int buttonId)
//{
//	if (pad == Pad::None) return false; // None�Ȃ画�ʕs�v
//	else if (pad == Pad::All) // All�w��̎��͑S�Ẵp�b�h
//	{    // �ċN�ďo���e�N�j�b�N
//		for (int i = 0; i < (int)Pad::NUM; i++)
//			if (GetButtonUp((Pad)i, buttonId))
//				return true; //������Ă���Pad�𔭌��I
//		return false; // ���������Ă��Ȃ�����
//	}
//	// 1�t���[���O�͉�����Ă��āA�����͉�����Ă���ꍇ��true��ԋp
//	return ((prevStates[(int)pad] & buttonId) & ~(currentStates[(int)pad] & buttonId)) != 0;
//}
//
////
////bool Input::IsMouseMoving()
////{
////	return ((prevMouseX != mouseX) && (prevMouseY != mouseY));//�����Ă�Ȃ�True��Ԃ�
////}
////
////bool Input::IsRStickMoving(Pad pad)
////{
////	return((stickInput[(int)pad].ThumbRX != 0) && (stickInput[(int)pad].ThumbRY != 0));//�����Ă�Ȃ�True��Ԃ�
////}
////
////bool Input::GetMouse(int button)
////{
////	return(mouseInput & button);//��������True�Ԃ�
////}
////
////bool Input::GetMouseDown(int button)
////{
////	return((mouseInput & button) & ~(prevMouseInput & button)) != 0;//�����u��True�Ԃ�
////}
////
////bool Input::GetMouseUp(int button)
////{
////	return((prevMouseInput & button) & ~(mouseInput & button)) != 0;//�����u��True�Ԃ�
////}

