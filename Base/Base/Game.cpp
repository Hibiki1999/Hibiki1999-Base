#include "Game.h"
#include "Scene/Child/Title/Title.h"
#include "Scene/Child/Playing/Playing.h"
#include "Scene/Child/Ending/Ending.h"
#include "Resource/Sound/BGM_Object/BGM_Object.h"
#include "Resource/Sound/SoundEffect_Object/SoundEffectObject.h"
#include "Library/GameManager/GameObjectManeger/GameObjectManager.h"

Scene* scenes;

Game::Game()
{
	//�e�V�[����ǂݍ���
	m_title = new Title(this);
	m_play = new Playing(this);
	m_ending = new Ending(this);
}

void Game::Init()
{
	Input::Init();//�Q�[���p�b�g��ǂݍ���
	MyRandom::Init();//������ǂݍ���
	Image::Init();//�摜��ǂݍ���
	gm.bgm = std::make_shared<BGM_Object>();
	gm.game_object_manager_ = std::make_shared<GameObjectManager>();
	MyDraw::InitMyDraw();
#ifdef _DEBUG

	Sound::Init();//�f�o�O���̂݉����̃p�X���m�F����

#endif // _DEBUG
	Game::ChangeScene(m_title);
}

void Game::Update()
{
	if (gm.bgm != nullptr)	gm.bgm->Update();
	Input::Update();
	scenes->Update();//�ǂݍ��܂��V�[���̖��b60��X�V
	for (const auto& se : gm.soundEffects)
	{
		se->Update();
	}
	gm.EraseRemoveIf(gm.soundEffects, [](std::shared_ptr<SoundEffectObject>& ptr) {return ptr->isDead; });

}

void Game::Draw()
{
	scenes->Draw();//�X�V�����V�[���̏󋵂��X�V
}

void Game::ChangeScene(Scene* scene)//�V�[����ς���Ƃ��ɁA�����ɌĂ΂��
{
	scenes = scene;//�Ă΂��̎��̃V�[�����`
	scenes->Init();//�ǂݍ��܂��V�[���̏�����
}
