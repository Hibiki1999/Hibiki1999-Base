#include "SoundEffectObject.h"

void SoundEffectObject::Update()
{
	if (CheckSoundMem(_Handle) == 0)//
	{
		isDead = true;
		DeleteSoundMem(_Handle);
	}
}
