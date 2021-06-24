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
class GameObjectManager;
class BGM_Object;
class SoundEffectManager;
class Camera;
class Map;
class DataSave;

class GameManager :public Singleton<GameManager>
{
public:
	friend class Singleton<GameManager>;

	std::shared_ptr<BGM_Object> bgm{ nullptr };

	std::shared_ptr<SoundEffectManager> soundEffects;

	std::shared_ptr<GameObjectManager> game_object_manager_;

	std::shared_ptr<Camera> camera_{ nullptr };

	std::shared_ptr<Map> map_{ nullptr };

	std::shared_ptr<DataSave> data_save_{ nullptr };

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
