#ifndef SOUND_EFFECT_OBJECT_H_
#define SOUND_EFFECT_OBJECT_H_

#include <string>
#include <DxLib.h>

class SoundEffectObject
{
public:
	SoundEffectObject(std::string _SoundEffect, int Volume, int playType = DX_PLAYTYPE_BACK);

	~SoundEffectObject() {};

	void Update();

	bool isDead = false;

	std::string tag = "";
private:


	int _Handle = -1;
};


#endif // !SOUND_EFFECT_OBJECT_H_