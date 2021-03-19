#ifndef CAMERA_H_
#define CAMERA_H_

#include "../Screen/Screen.h"
#include "../Input/Input.h"
#include "../Vec2/Vec2.h"
#include <DxLib.h>

class Camera
{
public:
	Camera() {};
	~Camera() {};

	static float x;
	static float y;

	static Vec2 mouseLocation;

	//�󔒂̕�����\�������Ȃ��悤�ɂ̏���
	static int MinCameraX;
	static int MinCameraY;
	static int MaxCameraX;
	static int MaxCameraY;

	static void LookAt(float targetX, float targetY)
	{
		x = targetX - Screen::Width / 2;
		y = targetY - Screen::Height / 2;


		//�󔒕�����\���������ꍇ�͂��̉��̎l�s���R�����g�A�E�g
		if (x < MinCameraX) x = MinCameraX;
		if (x > MaxCameraX) x = MaxCameraX;
		if (y < MinCameraY) y = MinCameraY;
		if (y > MaxCameraY) y = MaxCameraY;


		mouseLocation = Vec2(x + Input::mouseX, y + Input::mouseY);

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
