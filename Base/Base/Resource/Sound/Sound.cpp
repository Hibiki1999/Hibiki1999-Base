#include "Sound.h"
#include <string>

//int Sound::explo{ -1 };
//int Sound::shut{ -1 };
//int Sound::hit{ -1 };

std::string Sound::playingMusic;


void Sound::Load()
{
	/*explo = LoadSoundMem("Resource/Sound/SE/bomb.wav");
	assert(explo != -1);

	hit = LoadSoundMem("Resource/Sound/SE/hit49.wav");
	assert(hit != -1);

	shut = LoadSoundMem("Resource/Sound/SE/shut.wav");
	assert(shut != -1);*/
}

void Sound::Play(int handle,int Volume)
{
	ChangeVolumeSoundMem(Volume, handle);
	PlaySoundMem(handle, DX_PLAYTYPE_BACK);
}

void Sound::PlayMusic(std::string file, int Volume, int PlayType)
{
	if (file == playingMusic)return;
	DxLib::SetVolumeMusic(0);
	playingMusic = file;
	DxLib::PlayMusic(file.c_str(), PlayType);
}