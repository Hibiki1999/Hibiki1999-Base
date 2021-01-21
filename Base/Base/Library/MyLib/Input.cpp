#include "Input.h"

int Input::prevState{ 0 }; // 1�t���[���O�̏��
int Input::currentState{ 0 }; // ���݂̏��#include "Input.h"

void Input::Init()
{
	prevState = 0;
	currentState = 0;
}

// �ŐV�̓��͏󋵂ɍX�V���鏈���B
// ���t���[���̍ŏ��Ɂi�Q�[���̏�������Ɂj�Ă�ł��������B
void Input::Update()
{
	prevState = currentState;

	currentState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
}

// �{�^����������Ă��邩�H
bool Input::GetButton(int buttonId)
{
	// ���{�^����������Ă��邩�ǂ�����ԋp
	return (currentState & buttonId) != 0;
}

// �{�^���������ꂽ�u�Ԃ��H
bool Input::GetButtonDown(int buttonId)
{
	// ���͉�����Ă��āA����1�t���[���O�͉�����Ă��Ȃ��ꍇ��true��ԋp
	return ((currentState & buttonId) & ~(prevState & buttonId)) != 0;
}

// �{�^���������ꂽ�u�Ԃ��H
bool Input::GetButtonUp(int buttonId)
{
	// 1�t���[���O�͉�����Ă��āA�����͉�����Ă���ꍇ��true��ԋp
	return ((prevState & buttonId) & ~(currentState & buttonId)) != 0;
}