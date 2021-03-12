#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "../NotChangingLibrary/Singleton.h"

#include<vector>
#include <memory>

//class Player;
//class PlayerBullet;
//class Enemy;
//class EnemyBullet;
//class Explosion;
class Map;
class BGM_Object;
class SoundEffectObject;

class GameManager :public Singleton<GameManager>
{
public:
	friend class Singleton<GameManager>;

	std::shared_ptr<BGM_Object> bgm{ nullptr };

	std::vector < std::shared_ptr<SoundEffectObject>> soundEffects;

	/*std::shared_ptr<Map> map{ nullptr };

	std::shared_ptr<Player> player{ nullptr };

	std::vector<std::shared_ptr < PlayerBullet >> playerbullets;

	std::vector<std::shared_ptr < Enemy >> enemies;

	std::vector<std::shared_ptr <EnemyBullet>> enemyBullets;

	std::vector<std::shared_ptr <Explosion>> explosions;*/

	// ���폜���������ʃe���v���[�g�֐��ɂ���
  // [���ʃe���v���[�g�֐�]https://programming-place.net/ppp/contents/cpp/language/009.html#function_template
	template <typename T, class T_if>
	void EraseRemoveIf(std::vector<T>& v, T_if if_condition)
	{   //            ����̃^�C�vT��  ���z��v   ��������if_condition
		v.erase(
			std::remove_if(v.begin(), v.end(), if_condition),
			v.end() //  ��remove_if�̈ʒu
		);//��.[��][��][��][��][��]�� v.end()�̈ʒu
	};

protected:
	GameManager() {};
	virtual ~GameManager() {};
};

#endif // !GAMEMANAGER_H_
