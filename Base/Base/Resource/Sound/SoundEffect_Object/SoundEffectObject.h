#ifndef SOUND_EFFECT_OBJECT_H_
#define SOUND_EFFECT_OBJECT_H_

#include "../Sound.h"
#include "../../../Library/GameManager/GameManager.h"

class SoundEffectObject
{
public:
	SoundEffectObject(std::string _SoundEffect, int Volume, int playType = DX_PLAYTYPE_BACK)
	{
		_Handle = LoadSoundMem(_SoundEffect.c_str());
		ChangeVolumeSoundMem(Volume, _Handle);
		PlaySoundMem(_Handle, playType);
	};
	~SoundEffectObject() {};

	void Update();

	bool isDead = false;
private:
	GameManager& gm = GameManager::GetInstance();

	int _Handle;
};


#endif // !SOUND_EFFECT_OBJECT_H_