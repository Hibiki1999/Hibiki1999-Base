#include "Game.h"
#include "Scene/Child/TitleScene/TitleScene.h"
#include "Scene/Child/PlayingScene/PlayingScene.h"
#include "Resource/Sound/BGM_Object/BGM_Object.h"
#include "Resource/Sound/SoundEffectManager.h"
#include "Library/GameManager/GameObjectManeger/GameObjectManager.h"
#include "Library/DataSave/DataSave.h"
#include "Library/MyRandom/MyRandom.h"
#include "Library/MyDraw/MyDraw.h"
#include "Resource/Image/Image.h"
#include "Resource/Effect/Parents/EffectParent.h"
#include "Library/Input/Input.h"

Game::Game()
{
	//�e�V�[����ǂݍ���
	sm.register_scene("TitleScene", std::make_shared<TitleScene>());
	sm.register_scene("PlayingScene", std::make_shared<PlayingScene>());
}

void Game::Init()
{
	//Input::Init();//�Q�[���p�b�g��ǂݍ���
	MyRandom::Init();//������ǂݍ���
	Image::Init();//�摜��ǂݍ���
	MyDraw::InitMyDraw();
	gm.input = std::make_shared<Input>();
	RegisterButton();
	gm.bgm = std::make_shared<BGM_Object>();
	gm.game_object_manager_ = std::make_shared<GameObjectManager>();
	gm.soundEffects = std::make_shared<SoundEffectManager>();
	gm.data_save_ = std::make_shared<DataSave>();
	sm.change_scene("TitleScene");
}

void Game::Update()
{
	//Input::Update();
	gm.input->Update();
	gm.soundEffects->update();
	sm.update();//�ǂݍ��܂��V�[���̖��b60��X�V
	gm.bgm->Update();
	gm.soundEffects->remove();
	for (const auto& e : gm.effects) {
		e->Update();
	}
}

void Game::Draw()
{
	sm.draw();//�X�V�����V�[���̏󋵂��X�V
	for (const auto& e : gm.effects) {
		e->Draw();
	}
}

void Game::RegisterButton()
{
	/*
	*
	||===================================================================||
	||�g����PAD�{�^��													 ||
	||#define XINPUT_BUTTON_DPAD_UP			(0)	// �f�W�^�������{�^����	 ||
	||#define XINPUT_BUTTON_DPAD_DOWN		(1)	// �f�W�^�������{�^����  ||
	||#define XINPUT_BUTTON_DPAD_LEFT		(2)	// �f�W�^�������{�^����  ||
	||#define XINPUT_BUTTON_DPAD_RIGHT		(3)	// �f�W�^�������{�^���E	 ||
	||#define XINPUT_BUTTON_START			(4)	// START�{�^��			 ||
	||#define XINPUT_BUTTON_BACK			(5)	// BACK�{�^��			 ||
	||#define XINPUT_BUTTON_LEFT_THUMB		(6)	// ���X�e�B�b�N��������	 ||
	||#define XINPUT_BUTTON_RIGHT_THUMB		(7)	// �E�X�e�B�b�N��������	 ||
	||#define XINPUT_BUTTON_LEFT_SHOULDER	(8)	// LB�{�^��				 ||
	||#define XINPUT_BUTTON_RIGHT_SHOULDER	(9)	// RB�{�^��				 ||
	||#define XINPUT_BUTTON_A				(12)// A�{�^��				 ||
	||#define XINPUT_BUTTON_B				(13)// B�{�^��				 ||
	||#define XINPUT_BUTTON_X				(14)// X�{�^��				 ||
	||#define XINPUT_BUTTON_Y				(15)// Y�{�^��				 ||
	||===================================================================||
	||�g����L�[�{�[�h�{�^��											 ||
	||KEY_INPUT_A								// �`�L�[				 ||
	||�L�[�{�[�h�֐����������߁A����KEY_INPUT_A��F12�Ń��C�u�����ɂĎQ�l ||
	||===================================================================||
	||�g����}�E�X�{�^��                                                 ||
	||#define MOUSE_INPUT_LEFT				// �}�E�X���{�^��			 ||
	||#define MOUSE_INPUT_RIGHT				// �}�E�X�E�{�^��			 ||
	||#define MOUSE_INPUT_MIDDLE			// �}�E�X�����{�^��			 ||
	||#define MOUSE_INPUT_4					// �}�E�X�S�{�^��			 ||
	||#define MOUSE_INPUT_5					// �}�E�X�T�{�^��			 ||
	||#define MOUSE_INPUT_6					// �}�E�X�U�{�^��			 ||
	||#define MOUSE_INPUT_7					// �}�E�X�V�{�^��			 ||
	||#define MOUSE_INPUT_8					// �}�E�X�W�{�^��			 ||
	||===================================================================||
	*
	*/
	gm.input->RegisterButton("Forward", KEY_INPUT_W, InputType::KeyBoard);
	gm.input->RegisterButton("Backward", KEY_INPUT_S, InputType::KeyBoard);
	gm.input->RegisterButton("ToLeft", KEY_INPUT_A, InputType::KeyBoard);
	gm.input->RegisterButton("ToRight", KEY_INPUT_D, InputType::KeyBoard);
	gm.input->RegisterButton("Jump", KEY_INPUT_SPACE, InputType::KeyBoard);
	gm.input->RegisterButton("Forward", XINPUT_BUTTON_DPAD_UP, InputType::Pad);
	gm.input->RegisterButton("Backward", XINPUT_BUTTON_DPAD_DOWN, InputType::Pad);
	gm.input->RegisterButton("ToLeft", XINPUT_BUTTON_DPAD_LEFT, InputType::Pad);
	gm.input->RegisterButton("ToRight", XINPUT_BUTTON_DPAD_RIGHT, InputType::Pad);
	gm.input->RegisterButton("Jump", XINPUT_BUTTON_A, InputType::Pad);

}
/*

KEY_INPUT_BACK	// �o�b�N�X�y�[�X�L�[
KEY_INPUT_TAB	// �^�u�L�[
KEY_INPUT_RETURN	// �G���^�[�L�[

KEY_INPUT_LSHIFT	// ���V�t�g�L�[
KEY_INPUT_RSHIFT	// �E�V�t�g�L�[
KEY_INPUT_LCONTROL	// ���R���g���[���L�[
KEY_INPUT_RCONTROL	// �E�R���g���[���L�[
KEY_INPUT_ESCAPE	// �G�X�P�[�v�L�[
KEY_INPUT_SPACE	// �X�y�[�X�L�[
KEY_INPUT_PGUP	// �o�������t�o�L�[
KEY_INPUT_PGDN	// �o�������c�������L�[
KEY_INPUT_END	// �G���h�L�[
KEY_INPUT_HOME	// �z�[���L�[
KEY_INPUT_LEFT	// ���L�[
KEY_INPUT_UP	// ��L�[
KEY_INPUT_RIGHT	// �E�L�[
KEY_INPUT_DOWN	// ���L�[
KEY_INPUT_INSERT	// �C���T�[�g�L�[
KEY_INPUT_DELETE	// �f���[�g�L�[

KEY_INPUT_MINUS	// �|�L�[
KEY_INPUT_YEN	// ���L�[
KEY_INPUT_PREVTRACK	// �O�L�[
KEY_INPUT_PERIOD	// �D�L�[
KEY_INPUT_SLASH	// �^�L�[
KEY_INPUT_LALT	// ���`�k�s�L�[
KEY_INPUT_RALT	// �E�`�k�s�L�[
KEY_INPUT_SCROLL	// ScrollLock�L�[
KEY_INPUT_SEMICOLON	// �G�L�[
KEY_INPUT_COLON	// �F�L�[
KEY_INPUT_LBRACKET	// �m�L�[
KEY_INPUT_RBRACKET	// �n�L�[
KEY_INPUT_AT	// ���L�[
KEY_INPUT_BACKSLASH	// �_�L�[
KEY_INPUT_COMMA	// �C�L�[
KEY_INPUT_CAPSLOCK	// CaspLock�L�[
KEY_INPUT_PAUSE	// PauseBreak�L�[

KEY_INPUT_NUMPAD0	// �e���L�[�O
KEY_INPUT_NUMPAD1	// �e���L�[�P
KEY_INPUT_NUMPAD2	// �e���L�[�Q
KEY_INPUT_NUMPAD3	// �e���L�[�R
KEY_INPUT_NUMPAD4	// �e���L�[�S
KEY_INPUT_NUMPAD5	// �e���L�[�T
KEY_INPUT_NUMPAD6	// �e���L�[�U
KEY_INPUT_NUMPAD7	// �e���L�[�V
KEY_INPUT_NUMPAD8	// �e���L�[�W
KEY_INPUT_NUMPAD9	// �e���L�[�X
KEY_INPUT_MULTIPLY	// �e���L�[���L�[
KEY_INPUT_ADD	// �e���L�[�{�L�[
KEY_INPUT_SUBTRACT	// �e���L�[�|�L�[
KEY_INPUT_DECIMAL	// �e���L�[�D�L�[
KEY_INPUT_DIVIDE	// �e���L�[�^�L�[
KEY_INPUT_NUMPADENTER	// �e���L�[�̃G���^�[�L�[

KEY_INPUT_F1	// �e�P�L�[
KEY_INPUT_F2	// �e�Q�L�[
KEY_INPUT_F3	// �e�R�L�[
KEY_INPUT_F4	// �e�S�L�[
KEY_INPUT_F5	// �e�T�L�[
KEY_INPUT_F6	// �e�U�L�[
KEY_INPUT_F7	// �e�V�L�[
KEY_INPUT_F8	// �e�W�L�[
KEY_INPUT_F9	// �e�X�L�[
KEY_INPUT_F10	// �e�P�O�L�[
KEY_INPUT_F11	// �e�P�P�L�[
KEY_INPUT_F12	// �e�P�Q�L�[

KEY_INPUT_A	// �`�L�[
KEY_INPUT_B	// �a�L�[
KEY_INPUT_C	// �b�L�[
KEY_INPUT_D	// �c�L�[
KEY_INPUT_E	// �d�L�[
KEY_INPUT_F	// �e�L�[
KEY_INPUT_G	// �f�L�[
KEY_INPUT_H	// �g�L�[
KEY_INPUT_I	// �h�L�[
KEY_INPUT_J	// �i�L�[
KEY_INPUT_K	// �j�L�[
KEY_INPUT_L	// �k�L�[
KEY_INPUT_M	// �l�L�[
KEY_INPUT_N	// �m�L�[
KEY_INPUT_O	// �n�L�[
KEY_INPUT_P	// �o�L�[
KEY_INPUT_Q	// �p�L�[
KEY_INPUT_R	// �q�L�[
KEY_INPUT_S	// �r�L�[
KEY_INPUT_T	// �s�L�[
KEY_INPUT_U	// �t�L�[
KEY_INPUT_V	// �u�L�[
KEY_INPUT_W	// �v�L�[
KEY_INPUT_X	// �w�L�[
KEY_INPUT_Y	// �x�L�[
KEY_INPUT_Z	// �y�L�[
KEY_INPUT_0	// �O�L�[
KEY_INPUT_1	// �P�L�[
KEY_INPUT_2	// �Q�L�[
KEY_INPUT_3	// �R�L�[
KEY_INPUT_4	// �S�L�[
KEY_INPUT_5	// �T�L�[
KEY_INPUT_6	// �U�L�[
KEY_INPUT_7	// �V�L�[
KEY_INPUT_8	// �W�L�[
KEY_INPUT_9	// �X�L�[
*/