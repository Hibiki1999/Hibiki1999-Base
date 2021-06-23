#include "SoundEffectObject.h"
#include <assert.h>

SoundEffectObject::SoundEffectObject(std::string _SoundEffect, int Volume, int playType)
{
	std::string ads = "ResourceFile/SoundFile/SE/" + _SoundEffect;
	_Handle = LoadSoundMem(ads.c_str());
	ChangeVolumeSoundMem(Volume, _Handle);
	this->tag = _SoundEffect;
	PlaySoundMem(_Handle, playType);
};

void SoundEffectObject::Update()
{
	if (_Handle == -1)
	{
		assert(_Handle != -1);
		isDead = true;
		DeleteSoundMem(_Handle);
	}
	if (CheckSoundMem(_Handle) == 0)//
	{
		isDead = true;
		DeleteSoundMem(_Handle);
	}
}