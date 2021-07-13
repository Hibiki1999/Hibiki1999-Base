#ifndef GAME_OBJECT_MANAGER_H_
#define GAME_OBJECT_MANAGER_H_

#include <list>
#include <vector>
#include <string>
#include <memory>

#include "../../GameManager/GameManager.h"
class GameObject;

class GameObjectManager
{
public:
	//�f�t�H���h�R���X�g���N�^
	GameObjectManager() = default;
	//�f�X�g���N�^
	~GameObjectManager();
	//�A�N�^�[�̒ǉ�
	void add(std::shared_ptr<GameObject> gameObejct);
	//�A�N�^�[�̍X�V
	void update();
	//�`��
	void draw() const;
	//�A�N�^�[�̏Փ˔���
	void collide();
	//���S���Ă���A�N�^�[�̍폜
	void remove();
	//�A�N�^�[�̌���
	std::shared_ptr<GameObject> find(const std::string & name) const;
	//�w�肵���^�O�������A�N�^�[�̌���
	std::vector<std::shared_ptr<GameObject>> find_with_tag(const std::string & tag)const;
	//�A�N�^�[����Ԃ�
	int count() const;
	//�w�肵���^�O�������A�N�^�[����Ԃ�
	int count_with_tag(const std::string & tag)const;
	//����
	void clear();

	GameObjectManager(const GameObjectManager& other) = delete;
	GameObjectManager& operator = (const GameObjectManager& other) = delete;

private:
	//�A�N�^�[���X�g
	std::list<std::shared_ptr<GameObject>> game_object_;

	GameManager& gm = GameManager::GetInstance();

};
#endif // !GAME_OBJECT_MANAGER_H_

