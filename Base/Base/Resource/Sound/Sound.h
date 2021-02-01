#ifndef SOUND_H_
#define SOUND_H_

#include "DxLib.h"
#include <assert.h>
#include <string>

class Sound
{
public:
	Sound() {};
	~Sound() {};

	static void Load();

	static void Play(int handle,int Volume);

	static void PlayMusic(std::string file, int Volume, int PlayType = DX_PLAYTYPE_LOOP);

	/*static int explo;
	static int shut;
	static int hit;*/

	static std::string playingMusic;
};

#endif // !SOUND_H_

