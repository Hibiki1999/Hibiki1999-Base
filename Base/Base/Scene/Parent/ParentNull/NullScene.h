#ifndef NULL_SCENE_H_
#define NULL_SCENE_H_

#include "../Scene.h"

class NullScene:public Scene
{
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;
private:
};

#endif // !NULL_SCENE_H_
