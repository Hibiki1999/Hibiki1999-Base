#ifndef INPUT_H_
#define INPUT_H_

#include <DxLib.h>
#include <unordered_map>//�����z��

enum class Pad
{
	All = -2, // ���ׂĂ̂����ǂꂩ1�ł������ꂽ�Ƃ�
	None = -1,
	One,
	Two,
	Three,
	Four,
	NUM,
};

// ���̓N���X
class Input
{
public:
	// �Q�[���p�b�h�̃i���o�[
	static XINPUT_STATE stickInput[4];

	static int prevStates[(int)Pad::NUM]; // 1�t���[���O�̏��
	static int currentStates[(int)Pad::NUM]; // ���݂̏��

	static std::unordered_map<int, int> padDic;

	static void InitPadDictionary();//�����z��̏�����

	// �������B�ŏ���1�񂾂��Ă�ł��������B
	static void Init();

	// �ŐV�̓��͏󋵂ɍX�V���鏈���B
	// ���t���[���̍ŏ��Ɂi�Q�[���̏�������Ɂj�Ă�ł��������B
	static void Update();

	// �{�^����������Ă��邩�H
	static bool GetButton(Pad pad, int buttonId);

	// �{�^���������ꂽ�u�Ԃ��H
	static bool GetButtonDown(Pad pad, int buttonId);

	// �{�^���������ꂽ�u�Ԃ��H
	static bool GetButtonUp(Pad pad, int buttonId);

	//�E�X�e�B�b�N�������Ă邩
	static bool IsRStickMoving(Pad pad);

	//�}�E�X�̍��W���L�^
	static int mouseX, mouseY;
	static int prevMouseX, prevMouseY;

	//�}�E�X�������Ă邩
	static bool IsMouseMoving();

	//�}�E�X�O��t���[���̓��͂ƍ��̃t���[���̓��͂��擾
	static int prevMouseInput;
	static int mouseInput;

	static bool GetMouse(int button);//�}�E�X������Ă���

	static bool GetMouseDown(int button);//�}�E�X�������u��

	static bool GetMouseUp(int button);//�}�E�X�����u��
};

#endif
