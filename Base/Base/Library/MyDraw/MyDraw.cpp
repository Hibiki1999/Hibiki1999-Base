#include "MyDraw.h"
#include "../Transform/Transform.h"
#include <DxLib.h>

int MyDraw::DrawSphere3D(Vec3 center, float r, unsigned int SpcColor, unsigned int DifColor, int DivNum, int FillFlag)
{
    return DxLib::DrawSphere3D(VGet(center.x, center.y, center.z),r,DivNum,DifColor,SpcColor,FillFlag);
}

int MyDraw::SetCameraPositionAndTarget_UpVecY(Vec3 position, Vec3 lookpoint)
{
    VECTOR cvrt_position = VGet(position.x, position.y, position.z);
    VECTOR cvrt_look_point = VGet(lookpoint.x, lookpoint.y, lookpoint.z);
    return DxLib::SetCameraPositionAndTarget_UpVecY(cvrt_position, cvrt_look_point);
}

int MyDraw::Draw3DModel(int Model, Transform transform_)
{
    DxLib::MV1SetRotationXYZ(Model, VGet(transform_.rotation().pitch, transform_.rotation().yaw, transform_.rotation().roll));
    DxLib::MV1SetPosition(Model, VGet(transform_.position().x, transform_.position().y, transform_.position().z));
    DxLib::MV1SetScale(Model, VGet(1.0f, 1.0f, 1.0f));
    return DxLib::MV1DrawModel(Model);
}
