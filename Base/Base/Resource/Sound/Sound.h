#ifndef SOUND_H_
#define SOUND_H_

#include <DxLib.h>
#include <assert.h>
#include <string>
#include <vector>

#include "BGM_Object/BGM_Object.h"
#include "SoundEffect_Object/SoundEffectObject.h"

class Sound
{
public:
	Sound() {};
	~Sound() {};


#ifdef _DEBUG

	static void Init();

#endif // _DEBUG


	//static string�^�ŉ����t�@�C���̃p�X���w�肷��
	//BGM->"ResourceFile/SoundFile/BGM/"
	//SE-> "ResourceFile/SoundFile/SE/"
	//static std::string bgm1;

private:

#ifdef _DEBUG

	static std::vector<std::string> checkPath;
	static int check;
	static void LoadToList();//�w�肵���p�X�����X�g�ɓ���āA�����ǂ������m�F����

#endif // _DEBUG


};

#endif // !SOUND_H_

