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
	//デフォルドコンストラクタ
	GameObjectManager() = default;
	//デストラクタ
	~GameObjectManager();
	//アクターの追加
	void add(std::shared_ptr<GameObject> gameObejct);
	//アクターの更新
	void update();
	//描画
	void draw() const;
	//アクターの衝突判定
	void collide();
	//死亡しているアクターの削除
	void remove();
	//アクターの検索
	std::shared_ptr<GameObject> find(const std::string & name) const;
	//指定したタグ名を持つアクターの検索
	std::vector<std::shared_ptr<GameObject>> find_with_tag(const std::string & tag)const;
	//アクター数を返す
	int count() const;
	//指定したタグ名を持つアクター数を返す
	int count_with_tag(const std::string & tag)const;
	//消去
	void clear();

	GameObjectManager(const GameObjectManager& other) = delete;
	GameObjectManager& operator = (const GameObjectManager& other) = delete;

private:
	//アクターリスト
	std::list<std::shared_ptr<GameObject>> game_object_;

	GameManager& gm = GameManager::GetInstance();

};
#endif // !GAME_OBJECT_MANAGER_H_

