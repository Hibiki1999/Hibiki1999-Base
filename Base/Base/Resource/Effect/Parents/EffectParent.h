#ifndef EFFECT_PARENTS_H_
#define EFFECT_PARENTS_H_

#include <string>
#include <DxLib.h>
#include "../../../Library/Transform/Vec3/Vec3.h"

class EffectParent
{
public:
	bool isDead = false;
	bool isEnd = false;
	std::string tag = "";
	int drawLayer = 0;//大きいほど上の方に描画されます

	EffectParent() {};
	~EffectParent() {};

	virtual void Update()=0;

	virtual void Draw() = 0;

protected:
};

#endif // !EFFECT_PARENTS_H_