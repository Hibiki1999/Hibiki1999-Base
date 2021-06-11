#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../Parent/GameObject.h"
#include "../../../Library/Animation/Animation.h"	

class Player:public GameObject
{
public:
	Player(const Vec3 position);

	virtual void update() override;

	virtual void draw() const override;

	virtual void react(std::shared_ptr<GameObject> other)override;

private:

	enum Anim {
		Walk,
		Idle,
	};

	Anim animState = Idle;

	Animation anim = Animation(Image::ModelHandle);

	void AnimUpdate();

	void InputHandle();

};
#endif // !PLAYER_H_

