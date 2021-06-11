#ifndef CAMERA_H_
#define CAMERA_H_

#include "../../GameObject/Parent/GameObject.h"

class Camera : public GameObject
{
public:
	Camera();
	~Camera();

	virtual void update() override;

	virtual void draw() const override;

private:

	GameManager& gm = GameManager::GetInstance();

	Vec3 camera_location_ = Vec3(0, 0, 0);
	Vec3 look_point_ = Vec3(0, 0, 0);
};

#endif // !CAMERA_H_
