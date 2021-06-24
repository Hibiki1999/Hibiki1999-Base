#include "SceneManager.h"
#include "Parent/ParentNull/NullScene.h"

static std::shared_ptr<NullScene> null_scene_ = std::make_shared<NullScene>();

SceneManager::SceneManager()
	:current_scene_{null_scene_}
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::init()
{
	current_scene_->Init();
}

void SceneManager::update()
{
	current_scene_->Update();
}

void SceneManager::draw()
{
	current_scene_->Draw();
}

void SceneManager::finalize()
{
	current_scene_->Finalize();
	current_scene_ = null_scene_;
}

void SceneManager::change_scene(std::string nextScene)
{
	finalize();
	current_scene_ = scenes_[nextScene];
	init();
}

void SceneManager::register_scene(std::string SceneName, std::shared_ptr<Scene> sceneClass)
{
	scenes_[SceneName] = sceneClass;
}
