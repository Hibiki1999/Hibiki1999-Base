#include "BGM_Object.h"

#include <DxLib.h>
#include <assert.h>

void BGM_Object::PlayBGM1(std::string _BGM, int volume)
{
	if (_BGM1Name != _BGM)
	{
		_BGM1Name = _BGM;
		DeleteSoundMem(_BGM1);
		_BGM1 = -1;
	}
	else return;
	std::string ads = "ResourceFile/SoundFile/BGM/" + _BGM1Name;
	_BGM1 = LoadSoundMem(ads.c_str());
	assert(_BGM1 != -1);
	_BGM1Volume = volume;
	_BGM1FadeOutVolume = volume;
	ChangeVolumeSoundMem(_BGM1Volume, _BGM1);
	PlaySoundMem(_BGM1, DX_PLAYTYPE_LOOP);
}

void BGM_Object::FadeOutChangeBgm1(std::string _BGM, int volume)
{
	if (_BGM != _BGM1Name)
	{
		_BGM1Name = _BGM;
		_BGM1Volume = volume;
		ClearBool();
		StandBool(Bool::isBgm1FadeOutChange);
		return;
	}
	else return;
}

void BGM_Object::FadeOutAndDeleteBgm1()
{
	ClearBool();
	StandBool(isBgm1FadeOutAndDelete);
}

void BGM_Object::StopAndDeleteBgm1()
{
	DeleteSoundMem(_BGM1);
	_BGM1Name = "";
}

void BGM_Object::ChangeBgm1Volume(int Volume)
{
	_BGM1Volume = Volume;
	_BGM1FadeOutVolume = Volume;
	ChangeVolumeSoundMem(_BGM1Volume, _BGM1);
}

void BGM_Object::FadeOutAndStopBgm1()
{
	ClearBool();
	StandBool(Bool::isBgm1FadeOutAndStop);
}

void BGM_Object::FadeInAndContinueBgm1()
{
	ClearBool();
	StandBool(Bool::isBgm1ContinueAndFadeIn);
	PlaySoundMem(_BGM1, DX_PLAYTYPE_LOOP, 0);
}

void BGM_Object::PlayBGM2(std::string _BGM, int volume)
{
	if (_BGM2Name != _BGM)
	{
		_BGM2Name = _BGM;
		DeleteSoundMem(_BGM2);
		_BGM2 = -1;
	}
	else return;
	std::string ads = "ResourceFile/SoundFile/BGM/" + _BGM2Name;
	_BGM2 = LoadSoundMem(ads.c_str());
	assert(_BGM2 != -1);
	_BGM2Volume = volume;
	_BGM2FadeOutVolume = volume;
	ChangeVolumeSoundMem(_BGM2Volume, _BGM2);
	PlaySoundMem(_BGM2, DX_PLAYTYPE_LOOP);
}

void BGM_Object::FadeOutChangeBgm2(std::string _BGM, int volume)
{
	if (_BGM != _BGM2Name)
	{
		_BGM2Name = _BGM;
		_BGM2Volume = volume;
		ClearBool();
		StandBool(Bool::isBgm2FadeOutChange);
		return;
	}
	else return;
}

void BGM_Object::FadeOutAndDeleteBgm2()
{
	ClearBool();
	StandBool(isBgm2FadeOutAndDelete);
}

void BGM_Object::StopAndDeleteBgm2()
{
	DeleteSoundMem(_BGM2);
	_BGM2Name = "";
}

void BGM_Object::ChangeBgm2Volume(int Volume)
{
	_BGM2Volume = Volume;
	_BGM2FadeOutVolume = Volume;
	ChangeVolumeSoundMem(_BGM2Volume, _BGM2);
}

void BGM_Object::FadeOutAndStopBgm2()
{
	ClearBool();
	StandBool(isBgm2FadeOutAndStop);
}

void BGM_Object::FadeInAndContinueBgm2()
{
	ClearBool();
	StandBool(Bool::isBgm2ContinueAndFadeIn);
	PlaySoundMem(_BGM2, DX_PLAYTYPE_LOOP, 0);
}

void BGM_Object::Update()
{
	if (CheckBool(Bool::isBgm1FadeOutChange))ForBgm1FadeOutChange();
	if (CheckBool(Bool::isBgm1FadeOutAndStop)) { ForBgm1FadeOutAndStop(); }
	if (CheckBool(Bool::isBgm1ContinueAndFadeIn)) { ForBgm1ContinueAndFadeIn(); }
	if (CheckBool(Bool::isBgm2FadeOutChange))ForBgm2FadeOutChange();
	if (CheckBool(Bool::isBgm2FadeOutAndStop)) { ForBgm2FadeOutAndStop(); }
	if (CheckBool(Bool::isBgm2ContinueAndFadeIn)) { ForBgm2ContinueAndFadeIn(); }
	if (CheckBool(Bool::isBgm1FadeOutAndDelete)) { ForBgm1FadeOutAndDelete(); }
	if (CheckBool(Bool::isBgm2FadeOutAndDelete)) { ForBgm2FadeOutAndDelete(); }
}

inline void BGM_Object::ForBgm1FadeOutChange()
{
	if (_BGM1FadeOutVolume > 0)
	{
		_BGM1FadeOutVolume--;
		ChangeVolumeSoundMem(_BGM1FadeOutVolume, _BGM1);
	}
	else
	{
		DeleteSoundMem(_BGM1);
		_BGM1 = -1;
		std::string ads = "ResourceFile/SoundFile/BGM/" + _BGM1Name;
		assert(_BGM1 != -1);
		_BGM1 = LoadSoundMem(ads.c_str());
		_BGM1FadeOutVolume = _BGM1Volume;
		ChangeVolumeSoundMem(_BGM1Volume, _BGM1);
		PlaySoundMem(_BGM1, DX_PLAYTYPE_LOOP);
		BreakBool(Bool::isBgm1FadeOutChange);
		return;
	}
}

inline void BGM_Object::ForBgm2FadeOutChange()
{
	if (_BGM2FadeOutVolume > 0)
	{
		_BGM2FadeOutVolume--;
		ChangeVolumeSoundMem(_BGM2FadeOutVolume, _BGM2);
	}
	else
	{
		DeleteSoundMem(_BGM2);
		_BGM2 = -1;
		std::string ads = "ResourceFile/SoundFile/BGM/" + _BGM2Name;
		assert(_BGM2 != -1);
		_BGM2 = LoadSoundMem(ads.c_str());
		_BGM2FadeOutVolume = _BGM2Volume;
		ChangeVolumeSoundMem(_BGM2Volume, _BGM2);
		PlaySoundMem(_BGM2, DX_PLAYTYPE_LOOP);
		BreakBool(Bool::isBgm2FadeOutChange);
		return;
	}
}

inline void BGM_Object::ForBgm1FadeOutAndStop()
{
	if (_BGM1FadeOutVolume > 0)
	{
		_BGM1FadeOutVolume--;
		ChangeVolumeSoundMem(_BGM1FadeOutVolume, _BGM1);
	}
	else
	{
		StopSoundMem(_BGM1);
		BreakBool(Bool::isBgm1FadeOutAndStop);
	}
}

inline void BGM_Object::ForBgm1ContinueAndFadeIn()
{
	if (_BGM1FadeOutVolume < _BGM1Volume)
	{
		_BGM1FadeOutVolume++;
		ChangeVolumeSoundMem(_BGM1FadeOutVolume, _BGM1);
	}
	else
	{
		BreakBool(Bool::isBgm1ContinueAndFadeIn);
	}
}

inline void BGM_Object::ForBgm2FadeOutAndStop()
{
	if (_BGM2FadeOutVolume > 0)
	{
		_BGM2FadeOutVolume--;
		ChangeVolumeSoundMem(_BGM2FadeOutVolume, _BGM2);
	}
	else
	{
		StopSoundMem(_BGM2);
		BreakBool(Bool::isBgm2FadeOutAndStop);
	}
}

inline void BGM_Object::ForBgm2ContinueAndFadeIn()
{
	if (_BGM2FadeOutVolume < _BGM2Volume)
	{
		_BGM2FadeOutVolume++;
		ChangeVolumeSoundMem(_BGM2FadeOutVolume, _BGM2);
	}
	else
	{
		BreakBool(Bool::isBgm2ContinueAndFadeIn);
	}
}

inline void BGM_Object::ForBgm1FadeOutAndDelete()
{
	ForBgm1FadeOutAndStop();
	if (_BGM1FadeOutVolume <= 0)
	{
		StopAndDeleteBgm1();
		BreakBool(isBgm1FadeOutAndDelete);
	}
}
inline void BGM_Object::ForBgm2FadeOutAndDelete()
{
	ForBgm2FadeOutAndStop();
	if (_BGM2FadeOutVolume <= 0)
	{
		StopAndDeleteBgm2();
		BreakBool(isBgm2FadeOutAndDelete);
	}
}
