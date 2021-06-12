#include "CubeCollision.h"

CubeCollision::CubeCollision(float model_width, float model_height, const Vec3& position)
{
	this->position = position;
	this->center = position;
	this->center.y += model_height / 2;
	this->model_width_ = model_width;
	this->model_deep_ = model_width;
	this->model_height_ = model_height;
}

CubeCollision CubeCollision::transform(const Vec3& position)
{
	return CubeCollision{  model_width_,  model_height_, this->position = position };
}

bool CubeCollision::intersects(const CubeCollision& other) const
{
	return CubeCubeCollision(other) == true;
}

void CubeCollision::draw() const
{
	float front = position.z; front += model_deep_ / 2;
	float back  = position.z; back  -= model_deep_ / 2;
	float left  = position.x; left  -= model_width_ / 2;
	float right = position.x; right += model_width_ / 2;
	float top   = position.y; top   += model_height_;
	float bottom = position.y;

	DrawCube3D(VGet(left, bottom, front), VGet(right, bottom, back), GetColor(255, 0, 0), GetColor(255, 0, 0), 0);
}

Vec3 CubeCollision::GetScale()
{
	return Vec3(model_width_,model_height_,model_deep_);
}

bool CubeCollision::CubeCubeCollision(const CubeCollision& other) const
{
	float front = position.z; front += model_deep_ / 2;
	float back  = position.z; back  -= model_deep_ / 2;
	float left  = position.x; left  -= model_width_ / 2;
	float right = position.x; right += model_width_ / 2;
	float top   = position.y; top   += model_height_;

	float o_front = other.position.z;  o_front += other.model_deep_ / 2;
	float o_back  = other.position.z;  o_back  -= other.model_deep_ / 2;
	float o_left  = other.position.x;  o_left  -= other.model_width_ / 2;
	float o_right = other.position.x;  o_right += other.model_width_ / 2;
	float o_top   = other.position.y;  o_top   += other.model_height_;

	return((front > o_back) && (back < o_front) && (left < o_right) && (right > o_left) && (top > other.position.y) && (position.y < o_top));

}
