#include "Sound.h"
#include <string>

//int Sound::explo{ -1 };
//int Sound::shut{ -1 };
//int Sound::hit{ -1 };
//std::string Sound::bgm1{ "ResourceFile/SoundFile/BGM/1.mp3" };


#ifdef _DEBUG

std::vector<std::string> Sound::checkPath{ "0" };
int Sound::check{ -1 };

void Sound::Init()
{
	checkPath.clear();//���X�g���Y��ɂ���
	LoadToList();//�w�肵���p�X�����X�g�ɓ����
	for (int i = 0; i < checkPath.size(); i++)
	{
		check = LoadSoundMem(checkPath[i].c_str());//�������Ƀ��[�h���Ă݂�
		assert(check != -1);//���[�h���s������G���[���o��
		DeleteSoundMem(check);//���[�h�����������폜
		check = -1;//���̃��[�h������
	}
	checkPath.clear();//���X�g�̃����������炷
}

void Sound::LoadToList()
{
	//�����Ɋm�F�������p�X������
	//checkPath.push_back(bgm1);
}

#endif // _DEBUG

