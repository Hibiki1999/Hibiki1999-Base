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

	Vec3 look_point_ = Vec3(0, 0, 0);
private:

	GameManager& gm = GameManager::GetInstance();

	Vec3 camera_location_ = Vec3(0, 0, 0);

	float angle = 0;
	float angleY = 0;

	void FollowCamera(Vec3 targetPos, float targetOffsetHight, float length,Vec3 *CameraPos,Vec3 *CameraLookPosition);
};

#endif // !CAMERA_H_
