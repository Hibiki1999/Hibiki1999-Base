#ifndef SCENE_H_
#define SCENE_H_

#include <stdio.h>

class Scene
{
public:
	virtual ~Scene() = default;

	//�p�������V�[���̏�����
	virtual void Init() = 0;

	//�p�������V�[���̍X�V
	virtual void Update() = 0;

	//�X�V�����V�[����`��
	virtual void Draw() = 0;
};

#endif // !SCENE_H_
