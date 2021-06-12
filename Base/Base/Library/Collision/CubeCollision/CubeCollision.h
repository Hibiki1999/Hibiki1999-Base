#ifndef CUBE_COLLISION_H_
#define CUBE_COLLISION_H_

#include "../../Transform/Transform.h"

class CubeCollision
{
public:
	CubeCollision(float model_width = 0.0f, float model_height = 0.0f, const Vec3& position = Vec3{ 0.0f,0.0f,0.0f });

	CubeCollision transform(const Vec3& position);

	bool intersects(const CubeCollision& other)const;

	void draw() const;

	Vec3 GetScale();

private:

	float model_width_{ 0.0f };
	float model_deep_{ 0.0f };
	float model_height_{ 0.0f };

	Vec3 center{ 0.0f,0.0f,0.0f };
	Vec3 position{ 0.0f,0.0f,0.0f };

	bool CubeCubeCollision(const CubeCollision& other) const;
};

#endif // !CUBE_COLLISION_H_
