#include "SphereCollision.h"
#include "../../MyDraw/MyDraw.h"
#include "../../MyMath/MyMath.h"

SphereCollision::SphereCollision(float radius, const Vec3& center)
{
	this->radius = radius;
	this->center = center;
}

SphereCollision SphereCollision::translate(const Vec3& position) const
{
	return SphereCollision{ radius,center + position };
}

SphereCollision SphereCollision::transform() const
{
	return SphereCollision{ radius,center };
}

bool SphereCollision::intersects(const SphereCollision& other) const
{
	return SphereSphereCollision(other) == true;
}

void SphereCollision::draw() const
{
	MyDraw::DrawSphere3D(center, radius, GetColor(255, 0, 0), GetColor(255, 255, 255));

}

bool SphereCollision::SphereSphereCollision(const SphereCollision& other) const
{

	Vec3 v;
	v.x = MyMath::Square(other.center.x - center.x);
	v.y = MyMath::Square(other.center.y - center.y);
	v.z = MyMath::Square(other.center.z - center.z);
	float r = (float)std::pow(radius + other.radius, 2);

	return (v.x + v.y + v.z) <= r;
}
