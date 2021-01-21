#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string>

#include "../../Library/Mylib/MyMath.h"
#include "../../Library/Mylib/Screen.h"

class GameObject
{
public:

	std::string tag = "";

	float x = 0;
	float y = 0;
	bool isDead = false;

protected:
	int imageWidth = 0;
	int imageHeight = 0;
	int hitboxOffsetLeft = 0;
	int hitboxOffsetRight = 0;
	int hitboxOffsetTop = 0;
	int hitboxOffsetBottom = 0;

	GameObject()
	{
	}

	virtual ~GameObject()
	{
	}

	virtual float GetLeft()
	{
		return x + hitboxOffsetLeft;
	}

	virtual void SetLeft(float left)
	{
		x = left - hitboxOffsetLeft;
	}

	virtual float GetRight()
	{
		return x + imageWidth - hitboxOffsetRight;
	}

	virtual void SetRight(float right)
	{
		x = right + hitboxOffsetRight - imageWidth;
	}

	virtual float GetTop()
	{
		return y + hitboxOffsetTop;
	}

	virtual void SetTop(float top)
	{
		y = top - hitboxOffsetTop;
	}

	virtual float GetBottom()
	{
		return y + imageHeight - hitboxOffsetBottom;
	}

	virtual void SetBottom(float bottom)
	{
		y = bottom + hitboxOffsetBottom - imageHeight;
	}

	virtual void Update() = 0;

	virtual void Draw() = 0;
};

#endif // !GAMEOBJECT_H_

