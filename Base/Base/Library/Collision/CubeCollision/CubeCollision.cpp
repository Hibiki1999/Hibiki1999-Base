#include "CubeCollision.h"
#include "../../../Resource/Map/Map.h"

CubeCollision::CubeCollision(float model_width, float model_height, const Vec3& position)
{
	this->position = position;
	this->model_width_ = model_width;
	this->model_deep_ = model_width;
	this->model_height_ = model_height;
}

CubeCollision CubeCollision::transform(const Vec3& position)
{
	this->position = position;
	this->front_ = position.z + (model_deep_ / 2);
	this->back_ = position.z - (model_deep_ / 2);
	this->left_ = position.x - (model_width_ / 2);
	this->right_ = position.x + (model_width_ / 2);
	this->top_ = position.y + (model_height_);
	this->bottom_ = position.y;
	this->x_center_ = position.x;
	this->z_center_ = position.z;
	return CubeCollision{ model_width_,  model_height_, this->position };
}

bool CubeCollision::intersects(const CubeCollision& other) const
{
	return CubeCubeCollision(other) == true;
}

void CubeCollision::draw(const unsigned int spcColor, const unsigned int difColor, bool FillFlag) const
{
	DrawCube3D(VGet(left_, bottom_, front_), VGet(right_, bottom_, back_), difColor, spcColor, FillFlag);
	DrawCube3D(VGet(left_, top_, front_), VGet(right_, top_, back_), difColor, spcColor, FillFlag);
	DrawCube3D(VGet(left_, top_, front_), VGet(right_, bottom_, front_), difColor, spcColor, FillFlag);
	DrawCube3D(VGet(left_, top_, back_), VGet(right_, bottom_, back_), difColor, spcColor, FillFlag);
}

Vec3 CubeCollision::GetScale()
{
	return Vec3(model_width_, model_height_, model_deep_);
}

bool CubeCollision::CubeCubeCollision(const CubeCollision& other) const
{
	float o_front = other.position.z;  o_front += other.model_deep_ / 2;
	float o_back = other.position.z;  o_back -= other.model_deep_ / 2;
	float o_left = other.position.x;  o_left -= other.model_width_ / 2;
	float o_right = other.position.x;  o_right += other.model_width_ / 2;
	float o_top = other.position.y;  o_top += other.model_height_;

	return((front_ > o_back) && (back_ < o_front) && (left_ < o_right) && (right_ > o_left) && (top_ > other.position.y) && (position.y < o_top));

}

Vec3 CubeCollision::IsFrontWall(std::shared_ptr<Map> map, Vec3& position)
{
	float alpha_left = left_ + 20.0f;
	float alpha_right = right_ - 20.0f;

	if ((map->isWall(left_, front_) && map->isWall(alpha_left, front_)) ||
		map->isWall(x_center_, front_) ||
		(map->isWall(right_, front_) && map->isWall(alpha_right, front_))) {
		float wallBack = (front_ - (float)std::fmod(front_, map->CellSize)) - (model_deep_ / 2);
		position.z = wallBack;
	}
	else if ((map->isWall(left_, back_) && map->isWall(alpha_left, back_)) ||
		map->isWall(x_center_, back_) ||
		(map->isWall(right_, back_) && map->isWall(alpha_right, back_))) {
		float wallBack = (back_ - (float)std::fmod(back_, map->CellSize) + map->CellSize) + (model_deep_ / 2);
		position.z = wallBack;
	}
	return position;
}

Vec3 CubeCollision::IsBackWall(std::shared_ptr<Map> map, Vec3& position)
{
	if (map->isWall(left_, back_) ||
		map->isWall(x_center_, back_) ||
		map->isWall(right_, back_)) {
		float wallBack = (back_ - (float)std::fmod(back_, map->CellSize) + map->CellSize) + (model_deep_ / 2);
		position.z = wallBack;
	}
	return position;
}

Vec3 CubeCollision::IsLeftWall(std::shared_ptr<Map> map, Vec3& position)
{
	float alpha_front = front_ - 20.0f;
	float alpha_back = back_ + 20.0f;

	if ((map->isWall(left_, back_) && map->isWall(left_, alpha_back)) ||
		map->isWall(left_, z_center_) ||
		(map->isWall(left_, front_) && map->isWall(left_, alpha_front)))
	{
		float wallRight = (left_ - (float)std::fmod(left_, map->CellSize) + map->CellSize) + (model_width_ / 2);
		position.x = wallRight;
	}
	else if ((map->isWall(right_, back_) && map->isWall(right_, alpha_back)) ||
		map->isWall(right_, z_center_) ||
		(map->isWall(right_, front_) && map->isWall(right_, alpha_front)))
	{
		float wallLeft = (right_ - (float)std::fmod(right_, map->CellSize)) - (model_width_ / 2);
		position.x = wallLeft;
	}
	return position;
}

Vec3 CubeCollision::IsRightWall(std::shared_ptr<Map> map, Vec3& position)
{
	if (map->isWall(right_, back_) ||
		map->isWall(right_, x_center_) ||
		map->isWall(right_, front_))
	{
		float wallLeft = (right_ - (float)std::fmod(right_, map->CellSize)) - (model_width_ / 2);
		position.x = wallLeft;
	}
	return position;
}
