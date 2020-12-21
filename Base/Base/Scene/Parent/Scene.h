#pragma once
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