#ifndef CAMERA_H_
#define CAMERA_H_

#include "Screen.h"
#include "DxLib.h"

class Camera
{
public:
	Camera() {};
	~Camera() {};

	static float x;
	static float y;

	static void LookAt(float targetX, float targetY)
	{
		x = targetX - Screen::Width / 2;
		y = targetY - Screen::Height / 2;
	}

	static void DrawRotaGraphF(float worldX, float worldY, double exRate, double angle, int handle, int reverseXFlag = false, int transFlag = true)
	{
		DxLib::DrawRotaGraphF(worldX - x, worldY - y, exRate, angle, handle, transFlag, reverseXFlag);
	}

	static void DrawSquareHitBox(float left, float top, float right, float bottom, unsigned int color)
	{
		DrawBox((int)left - x + 0.5f,
				(int)(top - y + 0.5f),
				(int)(right - x + 0.5f),
				(int)(bottom - y + 0.5f),
				color, 0);
	}
};

#endif // !CAMERA_H_
