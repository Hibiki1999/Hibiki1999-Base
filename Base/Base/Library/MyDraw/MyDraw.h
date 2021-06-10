#ifndef MY_DRAW_H_
#define MY_DRAW_H_

struct Vec3;

class MyDraw
{
public:

	static int DrawSphere3D(Vec3 center, float r, unsigned int SpcColor, unsigned int DifColor, int DivNum = 32, int FillFlag = 0);
};

#endif // !MY_DRAW_H_

