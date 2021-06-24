#ifndef SCENE_H_
#define SCENE_H_

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

	//�V�[���̏I������
	virtual void Finalize() {}
};

#endif // !SCENE_H_
