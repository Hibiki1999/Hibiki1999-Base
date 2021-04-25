#ifndef BGM_OBJECT_H_
#define BGM_OBJECT_H_

#include "../Sound.h"
#include "../../../Library/GameManager/GameManager.h"

class BGM_Object
{
public:
	BGM_Object() {};
	~BGM_Object() {};

	void PlayBGM1(std::string _BGM, int volume);		 //BGM���Đ�
	void FadeOutChangeBgm1(std::string _BGM, int volume);//BGM���t�F�[�h�A�E�g���ĕς���
	void StopAndDeleteBgm1();							 //BGM���~�߂č폜����
	void ChangeBgm1Volume(int Volume);					 //BGM�̉��ʂ�ς���
	void FadeOutAndStopBgm1();							 //BGM���t�F�[�h�A�E�g���Ď~�߂�
	void FadeInAndContinueBgm1();						 //BGM�𑱂�����Đ����ăt�F�[�h�C������

	void PlayBGM2(std::string _BGM, int volume);		 //BGM���Đ�
	void FadeOutChangeBgm2(std::string _BGM, int volume);//BGM���t�F�[�h�A�E�g���ĕς���
	void StopAndDeleteBgm2();							 //BGM���~�߂č폜����
	void ChangeBgm2Volume(int Volume);					 //BGM�̉��ʂ�ς���
	void FadeOutAndStopBgm2();							 //BGM���t�F�[�h�A�E�g���Ď~�߂�
	void FadeInAndContinueBgm2();						 //BGM�𑱂�����Đ����ăt�F�[�h�C������

	void Update();

private:
	GameManager& gm = GameManager::GetInstance();

	enum Bool
	{
		isBgm1FadeOutChange = 1 << 0,
		isBgm2FadeOutChange = 1 << 1,
		isBgm1FadeOutAndStop = 1 << 2,
		isBgm1ContinueAndFadeIn = 1 << 3,
		isBgm2FadeOutAndStop = 1 << 4,
		isBgm2ContinueAndFadeIn = 1 << 5,
	};
	int allBool = 0;
	void StandBool(Bool b) { allBool |= b; }
	void BreakBool(Bool b) { allBool &= ~b; }
	bool CheckBool(Bool b) { return((allBool & b) == b); }

	int _BGM1 = -1;
	int _BGM1Volume = 0;
	int _BGM1FadeOutVolume = 0;
	std::string _BGM1Name = "";
	int _BGM2 = -1;
	int _BGM2Volume = 0;
	int _BGM2FadeOutVolume = 0;
	std::string _BGM2Name = "";

	inline void ForBgm1FadeOutChange();
	inline void ForBgm2FadeOutChange();

	inline void ForBgm1FadeOutAndStop();
	inline void ForBgm1ContinueAndFadeIn();

	inline void ForBgm2FadeOutAndStop();
	inline void ForBgm2ContinueAndFadeIn();
};

#endif // !BGM_OBJECT_H_