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
	//�R���X�g���N�^
	SceneManager();
	//�f�X�g���N�^
	~SceneManager();
	//������
	void init();
	//���t���[���A�b�v�f�[�g
	void update();
	//�`��
	void draw();
	//�I������
	void finalize();
	//�V�[���ύX
	void change_scene(std::string nextScene);
	//�V�[���ǉ�
	void register_scene(std::string SceneName,std::shared_ptr<Scene> sceneClass);

private:

	std::unordered_map<std::string, std::shared_ptr<Scene>> scenes_;
	
	std::shared_ptr<Scene> current_scene_;
};

#endif // !SCENE_MANAGER_H_
