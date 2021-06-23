#ifndef SOUND_H_
#define SOUND_H_

#include <string>
#include <list>
#include <memory>

#include "BGM_Object/BGM_Object.h"
#include "SoundEffect_Object/SoundEffectObject.h"

class SoundEffectManager
{
public:
	SoundEffectManager() {};
	~SoundEffectManager() {};
	//�T�E���h�G�t�F�N�g�ǉ�
	void add(std::string name, int volume);
	//�T�E���h�G�t�F�N�g�̍Đ����I��������H
	bool check_end(std::string name);
	//�T�E���h�G�t�F�N�g�̏�Ԍ���
	void update();
	//�T�E���h�G�t�F�N�g���������Ɏc��Ȃ��悤�ɍ폜
	void remove();

private:
	//�T�E���h�G�t�F�N�g���X�g
	std::list<std::shared_ptr<SoundEffectObject>> sound_effects_;

};

#endif // !SOUND_H_

