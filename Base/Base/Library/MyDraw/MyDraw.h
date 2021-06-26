#ifndef MY_DRAW_H_
#define MY_DRAW_H_

struct Vec3;
class Transform;
class DivImage;

#include <DxLib.h>

enum class Plane
{   // XYZ•½–Ê‚Ìw’è
	X = 1,
	Y,
	Z
};


class MyDraw
{
public:
	static Vec3 XYZ_ARROW;
	static bool IsReverseX_Texture;
	static bool IsReverseY_Texture;
	static bool IsReverseZ_Texture;

	static float CameraAngleHRotate;

	static void InitMyDraw();

	static int DrawSphere3D(Vec3 center, float r, unsigned int SpcColor, unsigned int DifColor, int DivNum = 32, int FillFlag = 0);

	static int SetCameraPositionAndTarget_UpVecY(Vec3 position, Vec3 lookpoint);

	static int Draw3DModel(int Model, Transform transform_);

	static void DrawDivRotaDivBoxF3D(float xf, float yf, float zf, double ExRate, Vec3 Angle, DivImage& divImage, int id, int TransFlag = true, int ReverseXFlag = false, int ReverseYFlag = false, int ReverseZFlag = false);

	static int DrawDivRotaGraphF3D(Plane plane, float xf, float yf, float zf, double ExRate, Vec3 Angle, DivImage& divImage, int id, int TransFlag = true, int ReverseXFlag = false, int ReverseYFlag = false, int ReverseZFlag = false);

	static int DrawDivRotaFloorF3D(Plane plane, float xf, float yf, float zf, double ExRate, double Angle, DivImage& divImage, int id, int TransFlag = true, int ReverseXFlag = false, int ReverseYFlag = false, int ReverseZFlag = false);

	// ‰æ‘œ‚Ì‰ñ“]•`‰æ( À•Ww’è‚ª float ”Å )
	static int DrawRotaGraphF3D(Plane plane, float xf, float yf, float zf, double ExRate, Vec3 Angle, int GrHandle, int TransFlag = TRUE, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE, int ReverseZFlag = FALSE);

	/// <summary>
	/// ”Âƒ|ƒŠƒSƒ“ƒLƒƒƒ‰‰æ‘œ‚ğ•`‰æ‚·‚éBí‚ÉƒJƒƒ‰•ûŒü‚É–Ê‚ğŒü‚¯‚Ä”Â‚Å‚ ‚é‚±‚Æ‚ª‚Î‚ê‚È‚¢‚æ‚¤‚É‚Å‚«‚é
	/// </summary>
	static void DrawPlaneCharaRotaGraphF3D(Vec3 position, double EXRate, double Angle, int handle, int TransFlag = TRUE);
	static int DrawPlaneDivCharaRotaGraphF3D(Vec3 position, double EXRate, double Angle, DivImage& divImage, int id, int TransFlag = TRUE, int ReverseXFlag = false, int ReverseYFlag = false, int ReverseZFlag = false);

	// ‰æ‘œ‚Ì‰ñ“]•`‰æ( À•Ww’è‚ª float ”Å )y’ˆÓIzŒ»óAngle‰ñ“]‹@”\‚Í–¢‘Î‰
	//static int DrawDivRotaGraphF3D(Plane plane, float xf, float yf, float zf, double ExRate, double Angle, DivImage& divImage, int id, int TransFlag = TRUE, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE, int ReverseZFlag = FALSE);


	static Vec3 VGet(float x, float y, float z);

private:
	static Vec3 VecAngle(Plane plane, double Angle);
};

#endif // !MY_DRAW_H_

