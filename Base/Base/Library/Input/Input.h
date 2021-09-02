#ifndef INPUT_H_
#define INPUT_H_

#include <DxLib.h>
#include <vector>
#include <string>

#include "../Transform/Vec2/Vec2.h"

//�{�^�����`���鎞�Ɏg���C���v�b�g�̎�ށA�����`�����Ɠ���Ȃ��ƃo�O��܂�
enum InputType {
	Pad,
	KeyBoard,
	Mouse,
};

class Input
{
public:
	//�C���v�b�g�𐶐��Apad��ς����4�̃R�����g���\�܂őΉ��ł���B�L�[�{�[�h�ƃ}�E�X���₹�Ȃ��̂Œ��ӁI
	Input(int pad = DX_INPUT_PAD1);
	~Input();
	//�C���v�b�g�̏�Ԃ��X�V
	void Update();
	//��`�����C���v�b�g�̖��O���L�[�{�[�h�A�}�E�X�A�p�b�g�Ɋ֌W�Ȃ��g����
	bool GetInput(std::string ActionName);
	bool GetInputDown(std::string ActionName);
	bool GetInputUp(std::string ActionName);
	//�p�b�g�̊e����
	bool GetPad(int buttonID);
	bool GetPad(std::string ActionName);
	bool GetPadDown(int buttonID);
	bool GetPadDown(std::string ActionName);
	bool GetPadUp(int buttonID);
	bool GetPadUp(std::string ActionName);
	Vec2 GetPadLStick();
	Vec2 GetPadRStick();
	float GetPadLTrigger();
	float GetPadRTrigger();
	//�L�[�{�[�h�̊e����
	bool GetKey(int keyId);
	bool GetKey(std::string ActionName);
	bool GetKeyDown(int keyId);
	bool GetKeyDown(std::string ActionName);
	bool GetKeyUp(int keyId);
	bool GetKeyUp(std::string ActionName);
	//�}�E�X�̊e����
	bool IsMouseMoving(Vec2 *velo);
	bool GetMouse(int button);
	bool GetMouse(std::string ActionName);
	bool GetMouseDown(int button);
	bool GetMouseDown(std::string ActionName);
	bool GetMouseUp(int button);
	bool GetMouseUp(std::string ActionName);
	Vec2 GetMousePosition();
	//�{�^����string�ɒ�`���A�ȒP�Ő؂�ւ����肷��
	void RegisterButton(std::string action, int buttonId, int inputType);
	//�}�E�X����ʂȂ��ɌŒ�
	void KeepCursorInScreen();
	//�}�E�X��\�����邩�H
	void IsShowCursor(bool b);
	//�C�ӃL�[
	bool AnyKeyDown();

private:

	//��`�o�^�p��
	enum {
		ActionName,
		InputID,
		InputType,
	};
	//vector����o�^�����{�^�����Ăяo��
	std::vector<int> InputIdFromList(std::string action, int inputType);
	//���̃p�b�g
	int input_pad_ = 0;
	//���̃p�b�g�̏��
	int pad_previous_state_[16] = { 0 };
	int pad_current_state_[16] = { 0 };
	//�L�[�{�[�g�̏��
	char key_previous_state_[256] = { '0' };
	char key_current_state_[256] = { '0' };
	//�}�E�X�O��t���[���̓��͂ƍ��̃t���[���̓��͂��擾
	int mouse_prev_state_ = 0;
	int mouse_current_state_ = 0;
	//�}�E�X�̍��W���L�^
	Vec2 mouse_current_position_ = Vec2(0, 0);
	Vec2 mouse_previos_position_ = Vec2(0, 0);
	int get_mouse_x_, get_mouse_y_ = 0;
	//��`�����{�^���̖��O�͂�����œo�^
	std::vector<std::vector<std::string>> buttonName;
	//�p�b�g�@�\���Ă�
	XINPUT_STATE input_;
};

#endif
