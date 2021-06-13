#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../Parent/GameObject.h"
#include "../../../Library/Animation/Animation.h"	

enum Anim {
	Walk,
	Idle,
};

class Player:public GameObject
{
public:
	Player(const Vec3 position);

	virtual void update() override;

	virtual void draw() const override;

	virtual void react(std::shared_ptr<GameObject> other)override;

private:

	Anim animState = Idle;

	Animation anim = Animation(Image::ModelHandle);

	void AnimUpdate();

	void InputHandle();

	Vec3 gravitypower={ 0.0f,-6.0f,0.0f };
	float maxgravpower = -30.0f;
	float jumppower = 60.0f;

};
#endif // !PLAYER_H_

