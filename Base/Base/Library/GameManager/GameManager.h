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

	// ★削除処理を共通テンプレート関数にする
  // [共通テンプレート関数]https://programming-place.net/ppp/contents/cpp/language/009.html#function_template
	template <typename T, class T_if>
	void EraseRemoveIf(std::vector<T>& v, T_if if_condition)
	{   //            特定のタイプT↑  ↑配列v   ↑条件式if_condition
		v.erase(
			std::remove_if(v.begin(), v.end(), if_condition),
			v.end() //  ↓remove_ifの位置
		);//例.[生][生][死][死][死]← v.end()の位置
	};

protected:
	GameManager() {};
	virtual ~GameManager() {};
};

#endif // !GAMEMANAGER_H_
