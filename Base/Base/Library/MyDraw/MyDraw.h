#ifndef MY_DRAW_H_
#define MY_DRAW_H_

struct Vec3;
class Transform;

class MyDraw
{
public:

	static int DrawSphere3D(Vec3 center, float r, unsigned int SpcColor, unsigned int DifColor, int DivNum = 32, int FillFlag = 0);

	static int SetCameraPositionAndTarget_UpVecY(Vec3 position, Vec3 lookpoint);

	static int Draw3DModel(int Model, Transform transform_);
};

#endif // !MY_DRAW_H_

