#ifndef INPUT_H_
#define INPUT_H_

#include <DxLib.h>
#include <vector>
#include <string>

class Input
{
public:

	Input(int pad = DX_INPUT_PAD1);
	~Input();

	void Update();

	bool GetPad(int buttonID);
	bool GetPad(std::string ActionName);
	bool GetPadDown(int buttonID);
	bool GetPadDown(std::string ActionName);
	bool GetPadUp(int buttonID);
	bool GetPadUp(std::string ActionName);

	void RegisterButton(std::string action, int buttonId);

private:

	enum {
		ActionName,
		ButtonID,
	};

	std::vector<int> ButtonIdFromList(std::string action);

	int input_pad_ = 0;

	int previous_state_[16] = { 0 };
	int current_state_[16] = { 0 };

	std::vector<std::vector<std::string>> buttonName;

	XINPUT_STATE input_;
};

#endif
//
//enum class Pad
//{
//	All = -2, // ���ׂĂ̂����ǂꂩ1�ł������ꂽ�Ƃ�
//	None = -1,
//	One,
//	Two,
//	Three,
//	Four,
//	NUM,
//};
//
//// ���̓N���X
//class Input
//{
//public:
//
//	// �������B�ŏ���1�񂾂��Ă�ł��������B
//	static void Init();
//
//	//�g�������{�^����o�^
//	static void RegisterButton(std::string action, int button);
//
//	// �ŐV�̓��͏󋵂ɍX�V���鏈���B
//	// ���t���[���̍ŏ��Ɂi�Q�[���̏�������Ɂj�Ă�ł��������B
//	static void Update();
//
//	// �{�^����������Ă��邩�H
//	static bool GetButton(Pad pad, std::string action);
//	static bool GetButton(Pad pad, int button);
//
//	// �{�^���������ꂽ�u�Ԃ��H
//	static bool GetButtonDown(Pad pad, std::string action);
//	static bool GetButtonDown(Pad pad, int button);
//
//	// �{�^���������ꂽ�u�Ԃ��H
//	static bool GetButtonUp(Pad pad, std::string action);
//	static bool GetButtonUp(Pad pad, int button);
//
//	////�E�X�e�B�b�N�������Ă邩
//	//static bool IsRStickMoving(Pad pad);
//	//
//	////�}�E�X�̍��W���L�^
//	//static int mouseX, mouseY;
//	//static int prevMouseX, prevMouseY;
//	//
//	////�}�E�X�������Ă邩
//	//static bool IsMouseMoving();
//	//
//	//�}�E�X�O��t���[���̓��͂ƍ��̃t���[���̓��͂��擾
//	//static int prevMouseInput;
//	//static int mouseInput;
//
//	//static bool GetMouse(int button);//�}�E�X������Ă���
//
//	//static bool GetMouseDown(int button);//�}�E�X�������u��
//
//	//static bool GetMouseUp(int button);//�}�E�X�����u��
//
//private:
//	enum
//	{
//		ButtonAction,
//		ButtonId,
//	};
//	// �Q�[���p�b�h�̃i���o�[
//	static XINPUT_STATE stickInput[4];
//
//	static int prevStates[(int)Pad::NUM]; // 1�t���[���O�̏��
//	static int currentStates[(int)Pad::NUM]; // ���݂̏��
//
//	static std::unordered_map<int, int> padDic;
//
//	static std::vector<std::vector<std::string>> buttonName;
//
//	static void InitPadDictionary();//�����z��̏�����
//
//	static bool isCurrentPressed(Pad pad, std::string action);
//	static bool isPreviousPressed(Pad pad, std::string action);
//};
