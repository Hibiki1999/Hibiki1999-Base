#include "MyDraw.h"
#include "../Transform/Transform.h"
#include <DxLib.h>

int MyDraw::DrawSphere3D(Vec3 center, float r, unsigned int SpcColor, unsigned int DifColor, int DivNum, int FillFlag)
{
    return DxLib::DrawSphere3D(VGet(center.x, center.y, center.z),r,DivNum,DifColor,SpcColor,FillFlag);
}
