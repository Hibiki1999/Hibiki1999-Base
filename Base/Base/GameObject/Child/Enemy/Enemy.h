#ifndef ENEMY_H_
#define ENEMY_H_

#include "../../Parent/GameObject.h"

class Enemy:public GameObject
{
public:
	Enemy(const Vec3 position);

	virtual void update() override;

	virtual void draw() const override;

	virtual void react(std::shared_ptr<GameObject> other) override;
};

#endif // !ENEMY_H_
