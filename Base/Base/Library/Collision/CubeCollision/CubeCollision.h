#ifndef CUBE_COLLISION_H_
#define CUBE_COLLISION_H_

#include "../../Transform/Transform.h"
#include "../../GameManager/GameManager.h"

class Map;

class CubeCollision
{
public:
	CubeCollision(float model_width = 0.0f, float model_height = 0.0f, const Vec3& position = Vec3{ 0.0f,0.0f,0.0f });

	CubeCollision transform(const Vec3& position);

	bool intersects(const CubeCollision& other)const;

	void draw(const unsigned int spcColor = GetColor(255, 0, 0), const unsigned int difColor = GetColor(255, 0, 0),bool FillFlag=false) const;

	Vec3 GetScale();

	Vec3 IsFrontWall(std::shared_ptr<Map> map, Vec3& position);
	Vec3 IsBackWall(std::shared_ptr<Map> map, Vec3& position);
	Vec3 IsLeftWall(std::shared_ptr<Map> map, Vec3& position);
	Vec3 IsRightWall(std::shared_ptr<Map> map, Vec3& position);
private:

	float model_width_{ 0.0f };
	float model_deep_{ 0.0f };
	float model_height_{ 0.0f };

	Vec3 position{ 0.0f,0.0f,0.0f };

	float front_ = 0.0f;
	float back_ = 0.0f;
	float left_ = 0.0f;
	float right_ = 0.0f;
	float top_ = 0.0f;
	float bottom_ = 0.0f;
	float x_center_ = 0.0f;
	float z_center_ = 0.0f;

	bool CubeCubeCollision(const CubeCollision& other) const;

};

#endif // !CUBE_COLLISION_H_
