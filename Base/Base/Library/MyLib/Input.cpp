#include "Input.h"

int Input::prevStates[]; // 1�t���[���O�̏��
int Input::currentStates[]; // ���݂̏��

std::unordered_map<int, int> Input::padDic; // �p�b�h�ԍ�����DX�̒�`�ւ̎���

void Input::InitPadDictionary()
{
	// �����z��őΉ��֌W�̎������쐬���Ă���
	padDic[(int)Pad::Key] = DX_INPUT_KEY;
	padDic[(int)Pad::One] = DX_INPUT_PAD1;
	padDic[(int)Pad::Two] = DX_INPUT_PAD2;
	padDic[(int)Pad::Three] = DX_INPUT_PAD3;
	padDic[(int)Pad::Four] = DX_INPUT_PAD4;
}

void Input::Init()
{
	InitPadDictionary();// �p�b�h�̎����z��̏�����

		// �L�[��Ԃ��[�����Z�b�g
	for (int i = 0; i < (int)Pad::NUM; i++)
		prevStates[i] = currentStates[i] = 0;
}

// �ŐV�̓��͏󋵂ɍX�V���鏈���B
// ���t���[���̍ŏ��Ɂi�Q�[���̏�������Ɂj�Ă�ł��������B
void Input::Update()
{
	for (int i = 0; i < (int)Pad::NUM; i++)
	{    // ���݂̏�Ԃ���O�̏�ԂƂ��ĕۑ�����GetJoypad..
		prevStates[i] = currentStates[i];
		currentStates[i] = GetJoypadInputState(padDic[i]);
	}
}

// �{�^����������Ă��邩�H
bool Input::GetButton(Pad pad, int buttonId)
{
	if (pad == Pad::None) return false; // None�Ȃ画�ʕs�v
	else if (pad == Pad::All) // All�w��̎��͑S�Ẵp�b�h
	{    // GetButton�̒���GetButton���Ăԁy�ċN�ďo���z�e�N�j�b�N
		for (int i = 0; i < (int)Pad::NUM; i++)
			if (GetButton((Pad)i, buttonId))
				return true; //������Ă���Pad�𔭌��I
		return false; // ���������Ă��Ȃ�����
	}
	// ���{�^����������Ă��邩�ǂ�����ԋp
	return (currentStates[(int)pad] & buttonId) != 0;
}

// �{�^���������ꂽ�u�Ԃ��H
bool Input::GetButtonDown(Pad pad, int buttonId)
{
	if (pad == Pad::None) return false; // None�Ȃ画�ʕs�v
	else if (pad == Pad::All) // All�w��̎��͑S�Ẵp�b�h
	{    // �ċN�ďo���e�N�j�b�N
		for (int i = 0; i < (int)Pad::NUM; i++)
			if (GetButtonDown((Pad)i, buttonId))
				return true; //������Ă���Pad�𔭌��I
		return false; // ���������Ă��Ȃ�����
	}
	// ���͉�����Ă��āA����1�t���[���O�͉�����Ă��Ȃ��ꍇ��true��ԋp
	return ((currentStates[(int)pad] & buttonId) & ~(prevStates[(int)pad] & buttonId)) != 0;
}

// �{�^���������ꂽ�u�Ԃ��H
bool Input::GetButtonUp(Pad pad, int buttonId)
{
	if (pad == Pad::None) return false; // None�Ȃ画�ʕs�v
	else if (pad == Pad::All) // All�w��̎��͑S�Ẵp�b�h
	{    // �ċN�ďo���e�N�j�b�N
		for (int i = 0; i < (int)Pad::NUM; i++)
			if (GetButtonUp((Pad)i, buttonId))
				return true; //������Ă���Pad�𔭌��I
		return false; // ���������Ă��Ȃ�����
	}
	// 1�t���[���O�͉�����Ă��āA�����͉�����Ă���ꍇ��true��ԋp
	return ((prevStates[(int)pad] & buttonId) & ~(currentStates[(int)pad] & buttonId)) != 0;
}