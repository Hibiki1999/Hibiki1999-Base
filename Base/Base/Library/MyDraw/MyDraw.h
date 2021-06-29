#ifndef MY_DRAW_H_
#define MY_DRAW_H_

struct Vec3;
class Transform;
class DivImage;

#include <DxLib.h>

enum class Plane
{   // XYZ平面の指定
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
	static Vec3 CameraPos;

	static void InitMyDraw();

	static int DrawSphere3D(Vec3 center, float r, unsigned int SpcColor, unsigned int DifColor, int DivNum = 32, int FillFlag = 0);

	static int SetCameraPositionAndTarget_UpVecY(Vec3 position, Vec3 lookpoint);

	static int Draw3DModel(int Model, Transform transform_);

	static void DrawDivRotaDivBoxF3D(float xf, float yf, float zf, double ExRate, Vec3 Angle, DivImage& divImage, int id, int TransFlag = true, int ReverseXFlag = false, int ReverseYFlag = false, int ReverseZFlag = false);

	static int DrawDivRotaGraphF3D(Plane plane, float xf, float yf, float zf, double ExRate, Vec3 Angle, DivImage& divImage, int id, int TransFlag = true, int ReverseXFlag = false, int ReverseYFlag = false, int ReverseZFlag = false);

	static int DrawDivRotaFloorF3D(Plane plane, float xf, float yf, float zf, double ExRate, double Angle, DivImage& divImage, int id, int TransFlag = true, int ReverseXFlag = false, int ReverseYFlag = false, int ReverseZFlag = false);

	// 画像の回転描画( 座標指定が float 版 )
	static int DrawRotaGraphF3D(Plane plane, float xf, float yf, float zf, double ExRate, Vec3 Angle, int GrHandle, int TransFlag = TRUE, int ReverseXFlag = FALSE, int ReverseYFlag = FALSE, int ReverseZFlag = FALSE);

	/// <summary>
	/// 板ポリゴンキャラ画像を描画する。常にカメラ方向に面を向けて板であることがばれないようにできる
	/// </summary>
	static void DrawPlaneCharaRotaGraphF3D(Vec3 position, double EXRate, double Angle, int handle, int TransFlag = TRUE);
	static int DrawPlaneDivCharaRotaGraphF3D(Vec3 position, double EXRate, double Angle, DivImage& divImage, int id, int TransFlag = TRUE, int ReverseXFlag = false, int ReverseYFlag = false, int ReverseZFlag = false);

	//エフェクト描画
	static void DrawEffect3D(Vec3 pos,float adjustZ, float size, float angle, int handle, int transFlag = true, int ReverseXFlag = false, int ReverseYFlag = false);


	static Vec3 VGet(float x, float y, float z);

private:
	static Vec3 VecAngle(Plane plane, double Angle);
};

#endif // !MY_DRAW_H_

