#ifndef BGM_OBJECT_H_
#define BGM_OBJECT_H_

#include "../Sound.h"
#include "../../../Library/GameManager/GameManager.h"

class BGM_Object
{
public:
	BGM_Object(std::string _BGM, int volume, int playType = DX_PLAYTYPE_LOOP)
	{
		this->isDead = false;
		this->m_Volume = volume;
		this->m_playType = playType;
		PlayMusic(_BGM.c_str(), playType);
	};

	~BGM_Object() {};

	int m_Volume=0;

	void Update()
	{
		SetVolumeMusic(m_Volume);
	}

private:
	GameManager& gm = GameManager::GetInstance();

	bool isDead;

	int m_playType = 0;
};

#endif // !BGM_OBJECT_H_