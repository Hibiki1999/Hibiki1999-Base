#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include "../Library/NotChangingLibrary/Singleton.h"
#include "../Scene/Parent/Scene.h"
#include <memory>
#include <unordered_map>
#include <string>

class SceneManager:public Singleton<SceneManager>
{
public:
	//コンストラクタ
	SceneManager();
	//デストラクタ
	~SceneManager();
	//初期化
	void init();
	//毎フレームアップデート
	void update();
	//描画
	void draw();
	//終了処理
	void finalize();
	//シーン変更
	void change_scene(std::string nextScene);
	//シーン追加
	void register_scene(std::string SceneName,std::shared_ptr<Scene> sceneClass);

private:

	std::unordered_map<std::string, std::shared_ptr<Scene>> scenes_;
	
	std::shared_ptr<Scene> current_scene_;
};

#endif // !SCENE_MANAGER_H_
