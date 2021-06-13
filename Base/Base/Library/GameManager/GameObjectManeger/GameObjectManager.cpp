#include "GameObjectManager.h"
#include "../../../GameObject/Parent/GameObject.h"

GameObjectManager::~GameObjectManager()
{
	clear();
}

void GameObjectManager::add(std::shared_ptr<GameObject> gameObejct)
{
	game_object_.push_back(gameObejct);
}

void GameObjectManager::update()
{
	for (auto go : game_object_) {
		go->update();
		go->WallCollide();
	}
}

void GameObjectManager::draw() const
{
	for (auto go : game_object_) {
		go->draw();
	}
	for (auto go : game_object_) {
		go->draw_transparent();
	}
	for (auto go : game_object_) {
		go->draw_gui();
	}
}

void GameObjectManager::collide()
{
	for (auto i = game_object_.begin(); i != game_object_.end(); i++) {
		for (auto j = std::next(i); j != game_object_.end(); j++) {
			(*i)->collide(*j);

		}
	}
}

void GameObjectManager::remove()
{
	for (auto i = game_object_.begin(); i != game_object_.end();) {
		if ((*i)->is_dead()) {
			i = game_object_.erase(i);
		}
		else {
			i++;
		}
	}
}

std::shared_ptr<GameObject> GameObjectManager::find(const std::string& name) const
{
	for (auto go : game_object_) {
		if (go->name() == name) {
			return go;
		}
	}
	return nullptr;
}

std::vector<std::shared_ptr<GameObject>> GameObjectManager::find_with_tag(const std::string& tag) const
{
	std::vector<std::shared_ptr<GameObject>> result_;
	for (auto go : game_object_) {
		if (go->tag() == tag) {
			result_.push_back(go);
		}
	}
	return result_;
}

int GameObjectManager::count() const
{
	return (int)game_object_.size();
}

int GameObjectManager::count_with_tag(const std::string& tag) const
{
	int result = 0;
	for (auto go : game_object_) {
		if (go->tag() == tag) {
			result++;
		}
	}
	return result;
}

void GameObjectManager::clear()
{
	game_object_.clear();
}
