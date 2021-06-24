#ifndef SCENE_H_
#define SCENE_H_

class Scene
{
public:
	virtual ~Scene() = default;

	//継承したシーンの初期化
	virtual void Init() = 0;

	//継承したシーンの更新
	virtual void Update() = 0;

	//更新したシーンを描画
	virtual void Draw() = 0;

	//シーンの終了処理
	virtual void Finalize() {}
};

#endif // !SCENE_H_
