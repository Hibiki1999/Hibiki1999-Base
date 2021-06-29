#include "MyDraw.h"
#include "../Transform/Transform.h"
#include "../../Resource/Image/Image.h"
#include <DxLib.h>

Vec3 MyDraw::XYZ_ARROW = VGet(1, -1, 1);
bool MyDraw::IsReverseX_Texture{ false };
bool MyDraw::IsReverseY_Texture{ false };
bool MyDraw::IsReverseZ_Texture{ false };
float MyDraw::CameraAngleHRotate{ 0.0f };
Vec3 MyDraw::CameraPos = { 0.0f,0.0f,0.0f };

void MyDraw::InitMyDraw()
{
	SetUseZBuffer3D(1);
	SetWriteZBuffer3D(1);
}

int MyDraw::DrawSphere3D(Vec3 center, float r, unsigned int SpcColor, unsigned int DifColor, int DivNum, int FillFlag)
{
	return DxLib::DrawSphere3D(DxLib::VGet(center.x, center.y, center.z), r, DivNum, DifColor, SpcColor, FillFlag);
}

int MyDraw::SetCameraPositionAndTarget_UpVecY(Vec3 position, Vec3 lookpoint)
{
	VECTOR cvrt_position = position.Conv();//DxLib::VGet(position.x, position.y, position.z);
	VECTOR cvrt_look_point = lookpoint.Conv();//DxLib::VGet(lookpoint.x, lookpoint.y, lookpoint.z);
	return DxLib::SetCameraPositionAndTarget_UpVecY(cvrt_position, cvrt_look_point);
}

int MyDraw::Draw3DModel(int Model, Transform transform_)
{
	DxLib::MV1SetRotationXYZ(Model, DxLib::VGet(transform_.rotation().pitch * (3.1415f / 180.0f), transform_.rotation().yaw * (3.1415f / 180.0f), transform_.rotation().roll * (3.1415f / 180.0f)));
	DxLib::MV1SetPosition(Model, DxLib::VGet(transform_.position().x, transform_.position().y, transform_.position().z));
	DxLib::MV1SetScale(Model, DxLib::VGet(1.0f, 1.0f, 1.0f));
	return DxLib::MV1DrawModel(Model);
}

void MyDraw::DrawDivRotaDivBoxF3D(float xf, float yf, float zf, double ExRate, Vec3 Angle, DivImage& divImage, int id, int TransFlag, int ReverseXFlag, int ReverseYFlag, int ReverseZFlag)
{
	float imageWidth = (float)divImage.XSize * (float)ExRate;
	float imageHeight = (float)divImage.YSize * (float)ExRate;

	float adjust_y_ = (((float)ExRate - 1.0f) * 16.0f);

	//�T�C�R����6�ʂ�`��
	DrawDivRotaGraphF3D(Plane::Y, xf, yf - (imageHeight / 2) + adjust_y_, zf, ExRate, Angle, divImage, id, TransFlag, ReverseXFlag, ReverseYFlag, ReverseZFlag);
	DrawDivRotaGraphF3D(Plane::Y, xf, yf + (imageHeight / 2) + adjust_y_, zf, ExRate, Angle, divImage, id, TransFlag, ReverseXFlag, ReverseYFlag, ReverseZFlag);
	// X�����̗����͍��E���]
	DrawDivRotaGraphF3D(Plane::X, xf - (imageWidth / 2), yf + adjust_y_, zf, ExRate, Angle, divImage, id, TransFlag, ReverseXFlag, ReverseYFlag, !ReverseZFlag);
	DrawDivRotaGraphF3D(Plane::X, xf + (imageWidth / 2), yf + adjust_y_, zf, ExRate, Angle, divImage, id, TransFlag, ReverseXFlag, ReverseYFlag, ReverseZFlag);
	DrawDivRotaGraphF3D(Plane::Z, xf, yf + adjust_y_, zf - (imageHeight / 2), ExRate, Angle, divImage, id, TransFlag, ReverseXFlag, ReverseYFlag, ReverseZFlag);
	// Z�����̗����͍��E���]
	DrawDivRotaGraphF3D(Plane::Z, xf, yf + adjust_y_, zf + (imageHeight / 2), ExRate, Angle, divImage, id, TransFlag, !ReverseXFlag, ReverseYFlag, ReverseZFlag);
	return;
}

int MyDraw::DrawDivRotaGraphF3D(Plane plane, float xf, float yf, float zf, double ExRate, Vec3 Angle, DivImage& divImage, int id, int TransFlag, int ReverseXFlag, int ReverseYFlag, int ReverseZFlag)
{
	// ����������͕̂`���Ȃ��ő�return
	//if (zf > farClipPlane) return -1;

	// �E��E����n��Y�����̕����ɏ]�����W��ϊ�
	Vec3 COVERT_XYZ = Vec3(xf, yf, zf);
	float Xf = COVERT_XYZ.x, Yf = COVERT_XYZ.y, Zf = COVERT_XYZ.z;

	if (id < 0 && divImage.AllNum <= id) { assert("div�摜id�w��͈͊O" == ""); return -1; }

	int imageWidth = divImage.XSize;
	int imageHeight = divImage.YSize;
	float u_X0 = 0.0F, v_Y0 = 0.0F; //�_Vertex[0]��u��v�̒l
	float u_X3 = 1.0F, v_Y3 = 1.0F; //�_Vertex[3]��u��v�̒l
	if (divImage.XNum > 1 || divImage.YNum > 1)
	{   // div�����摜�̕����ʒu�m��̂��߉�u�Əcv�̒l���v�Z
		int divX = id % divImage.XNum;//����X��ԍ�
		int divY = id / divImage.XNum;//����Y�s�ԍ�
		u_X0 = (float)divX / (float)(divImage.XNum);
		v_Y0 = (float)divY / (float)(divImage.YNum);
		u_X3 = (float)(divX + 1) / (float)(divImage.XNum);
		v_Y3 = (float)(divY + 1) / (float)(divImage.YNum);
	}



	// �y�g��k����ExRate�z�������ĉ摜�T�C�Y���Čv�Z
	imageWidth = (int)(imageWidth * ExRate);  // �g��k�������摜�̕�
	imageHeight = (int)(imageHeight * ExRate);// �g��k�������摜�̍���
	float halfWidth = (float)(imageWidth / 2);//�摜����1/2(��Ɍv�Z���g���܂킵�ď����팸)
	float halfHeight = (float)(imageHeight / 2);//�摜������1/2(��Ɍv�Z���g���܂킵�ď����팸)
	//�y�e�N�X�`�����]�����z��halfWidth�ƍ���halfHeight���}�C�i�X�ɂ��邱�ƂŔ��]
	// ��ReverseXFlag��IsReverseX_Texture�������]�́y���]�̔��]��=���]���Ȃ�!�z
	// �y���]�̔��]��=���]���Ȃ�!�z�́�XOR�y�r���I�_���a ^ ���Z�q�z
	if ((IsReverseX_Texture ^ (ReverseXFlag == TRUE))
		&& (plane == Plane::Y || plane == Plane::Z))
	{   // �}�C�i�X���Ńe�N�X�`�����]
		halfWidth = -halfWidth;
	}
	if ((IsReverseY_Texture ^ (ReverseYFlag == TRUE))
		&& (plane == Plane::X || plane == Plane::Z))
	{   // �}�C�i�X���Ńe�N�X�`�����]
		halfHeight = -halfHeight;
	}
	if (IsReverseZ_Texture ^ (ReverseZFlag == TRUE))
	{   // �}�C�i�X���Ńe�N�X�`�����]
		if (plane == Plane::X) halfWidth = -halfWidth;
		if (plane == Plane::Y) halfHeight = -halfHeight;
	}

	// ��CG�́y�ŏ��P�ʂ͎O�p�`�z2D�̓h�b�g�̏W���ŕ`�����yCG�͎O�p�`�̏W���ŕ`���z
	VERTEX_3D Vertex[6]; // �|���S���Q���Ȃ̂ŁA���_�͂U��(�O�p3�_�~2)

	// �����_���̃Z�b�g
	{   // Plane=X �Ȃ� X���ʂ�(Y,Z) = (yf,zf)���S�ɕ`��
		// Plane=Y �Ȃ� Y���ʂ�(X,Z) = (xf,zf)���S�ɕ`��
		// Plane=Z �Ȃ� Z���ʂ�(X,Y) = (xf,yf)���S�ɕ`��
		// ��]�͈ȉ������N�Q��
		// https://dxlib.xsrv.jp/cgi/patiobbs/patio.cgi?mode=past&no=2749
		MATRIX TransformMatrix;
		// ��]( x, y, z����]�̏��ɉ�]������A���W�ړ��s��ɂ�蕽�s�ړ�)
		// ����MMult�͍s��̏�Z�y��Z��������x����]��y����]��z����]�����s�ړ��z
		//���y��������]�͓�����������̂ŃN�H�[�^�j�I������������������z
		TransformMatrix = MGetRotX(Angle.x);
		TransformMatrix = MMult(TransformMatrix, MGetRotY(Angle.y));
		TransformMatrix = MMult(TransformMatrix, MGetRotZ(Angle.z));
		//���y���W�ړ��s��ɂ��ړ��z
		TransformMatrix = MMult(TransformMatrix, MGetTranslate(DxLib::VGet(Xf, Yf, Zf)));

		if (plane == Plane::X)
		{   //���W�Œ蕽�ʁ�������������������X���ʎw��
			Vertex[0].pos = VTransform(DxLib::VGet(0.0F, +halfHeight, -halfWidth), TransformMatrix);
			Vertex[1].pos = VTransform(DxLib::VGet(0.0F, +halfHeight, +halfWidth), TransformMatrix);
			Vertex[2].pos = VTransform(DxLib::VGet(0.0F, -halfHeight, -halfWidth), TransformMatrix);
			Vertex[3].pos = VTransform(DxLib::VGet(0.0F, -halfHeight, +halfWidth), TransformMatrix);
		}
		else if (plane == Plane::Y)
		{   //���W�Œ蕽�ʁ���������������������������������Y���ʎw��
			Vertex[0].pos = VTransform(DxLib::VGet(-halfWidth, 0.0F, +halfHeight), TransformMatrix);
			Vertex[1].pos = VTransform(DxLib::VGet(+halfWidth, 0.0F, +halfHeight), TransformMatrix);
			Vertex[2].pos = VTransform(DxLib::VGet(-halfWidth, 0.0F, -halfHeight), TransformMatrix);
			Vertex[3].pos = VTransform(DxLib::VGet(+halfWidth, 0.0F, -halfHeight), TransformMatrix);
		}
		else // if (plane == Plane::Z)
		{   //���W�Œ蕽�ʁ���������������������������������������������������Z���ʎw��
			Vertex[0].pos = VTransform(DxLib::VGet(-halfWidth, +halfHeight, 0.0F), TransformMatrix);
			Vertex[1].pos = VTransform(DxLib::VGet(+halfWidth, +halfHeight, 0.0F), TransformMatrix);
			Vertex[2].pos = VTransform(DxLib::VGet(-halfWidth, -halfHeight, 0.0F), TransformMatrix);
			Vertex[3].pos = VTransform(DxLib::VGet(+halfWidth, -halfHeight, 0.0F), TransformMatrix);
		}
		Vertex[4].pos = Vertex[2].pos; // �_2�Ɠ_4�͓����ʒu
		Vertex[5].pos = Vertex[1].pos; // �_1�Ɠ_5�͓����ʒu
		//���_0 �_1&5 �_4&2 �_3 ��4�_�̎l�p�`��`��

		// ��div�����摜���l���ɓ���āyUV�W�J�z�؂�o���ʒu��0.0�`1.0�Ŏw��
		Vertex[0].u = u_X0; Vertex[0].v = v_Y0;
		Vertex[1].u = u_X3; Vertex[1].v = v_Y0;
		Vertex[2].u = u_X0; Vertex[2].v = v_Y3;
		Vertex[3].u = u_X3; Vertex[3].v = v_Y3;
		Vertex[4].u = u_X0; Vertex[4].v = v_Y3;
		Vertex[5].u = u_X3; Vertex[5].v = v_Y0;

		// �P�x(���邳)�͑S�n�_100%
		Vertex[0].r = Vertex[0].g = Vertex[0].b = 255;
		Vertex[1].r = Vertex[1].g = Vertex[1].b = 255;
		Vertex[2].r = Vertex[2].g = Vertex[2].b = 255;
		Vertex[3].r = Vertex[3].g = Vertex[3].b = 255;
		Vertex[4].r = Vertex[4].g = Vertex[4].b = 255;
		Vertex[5].r = Vertex[5].g = Vertex[5].b = 255;

		// a(�A���t�@�s�����x) ���ő�l(255=�s���� 0=����)
		Vertex[0].a = 255; Vertex[1].a = 255;
		Vertex[2].a = 255;
		Vertex[5].a = 255;
		Vertex[4].a = 255; Vertex[3].a = 255;
		//����̏��̓_�œ_0 �_1&5 �_4&2 �_3 ��4�_�̎l�p�`��`��
	}

	// �|���S�����Q���`��
	return DrawPolygon3D(Vertex, 2, divImage.HandleArray[id], TransFlag);
}

int MyDraw::DrawDivRotaFloorF3D(Plane plane, float xf, float yf, float zf, double ExRate, double Angle, DivImage& divImage, int id, int TransFlag, int ReverseXFlag, int ReverseYFlag, int ReverseZFlag)
{
	Vec3 AngleVec = VecAngle(plane, Angle);
	int imageHeight = divImage.YSize;
	//                                              �p�x������VECTOR��
	return DrawDivRotaGraphF3D(plane, xf, yf - imageHeight / 2, zf, ExRate, AngleVec, divImage, id, TransFlag, ReverseXFlag, ReverseYFlag, ReverseZFlag);
}

int MyDraw::DrawRotaGraphF3D(Plane plane, float xf, float yf, float zf, double ExRate, Vec3 Angle, int GrHandle, int TransFlag, int ReverseXFlag, int ReverseYFlag, int ReverseZFlag)
{   // 1�~1�̒P��摜�Ƃ���GrHandle�������p��
	int imageWidth, imageHeight;
	GetGraphSize(GrHandle, &imageWidth, &imageHeight);
	DivImage divImage{ 1,1,imageWidth,imageHeight };
	divImage.HandleArray[0] = GrHandle;
	return DrawDivRotaGraphF3D(plane, xf, yf, zf, ExRate, Angle, divImage, 0, TransFlag, ReverseXFlag, ReverseYFlag, ReverseZFlag);
}   // ����������div�Ή��Ŋ֐��Ɉ����p��

Vec3 MyDraw::VGet(float x, float y, float z)
{   // DX���C�u������3D�`����W�n�ɕϊ�
	if (XYZ_ARROW.x == 1 && XYZ_ARROW.y == 1 && XYZ_ARROW.z == 1)
	{   // DX �f�t�H���g2D�`����W�n
		return VGet(x, y, z);
	}
	else if (XYZ_ARROW.x == 1 && XYZ_ARROW.y == -1 && XYZ_ARROW.z == 1)
	{   // DX 3D�`����W�n
		return VGet(x, -y, z);
	}

	Vec3 Result;
	if (XYZ_ARROW.x == 1) Result.x = x;
	else Result.x = -x;
	if (XYZ_ARROW.y == 1) Result.y = y;
	else Result.y = -y;
	if (XYZ_ARROW.z == 1) Result.z = z;
	else Result.z = -z;
	return Result;
}

Vec3 MyDraw::VecAngle(Plane plane, double Angle)
{
	Vec3 AngleVec = VGet(0.0F, 0.0F, 0.0F);
	// ���ʂɍ��킹�ĉ�]����I��
	if (plane == Plane::X) AngleVec.x = (float)Angle;
	else if (plane == Plane::Y) AngleVec.y = (float)Angle;
	else if (plane == Plane::Z) AngleVec.z = (float)Angle;

	return AngleVec;
}

void MyDraw::DrawPlaneCharaRotaGraphF3D(Vec3 position, double EXRate, double Angle, int handle, int TransFlag)
{   // �ۑ����ꂽ�L�����̊p�x���g���|���S�����J�����ɖʂ�������悤�ɂ���
	float x = 0.0f;
	float y = 0.0f;
	GetGraphSizeF(handle, &x, &y);
	Vec3 planeCharaAngle = Vec3(0, MyDraw::CameraAngleHRotate, (float)Angle);
	MyDraw::DrawRotaGraphF3D(Plane::Z, position.x, position.y + (y / 2), position.z, 1, planeCharaAngle, handle, TRUE);
}

int MyDraw::DrawPlaneDivCharaRotaGraphF3D(Vec3 position, double EXRate, double Angle, DivImage& divImage, int id, int TransFlag, int ReverseXFlag, int ReverseYFlag, int ReverseZFlag)
{
	float y = (float)divImage.YSize * (float)EXRate;
	position.y += (y / 2.0f);
	Vec3 toCameraAngle = (CameraPos - position).Normalized();
	//toCameraAngle += 90;
	Vec3 planeCharaAngle = Vec3(0, MyDraw::CameraAngleHRotate, (float)Angle);
	return DrawDivRotaGraphF3D(Plane::Z, position.x, position.y, position.z, EXRate, toCameraAngle, divImage, id, TransFlag, ReverseXFlag, ReverseYFlag, ReverseZFlag);
}

void MyDraw::DrawEffect3D(Vec3 pos, float adjustZ, float size, float angle, int handle, int transFlag, int ReverseXFlag, int ReverseYFlag)
{
	VECTOR VPos = pos.Conv();
	VPos.z -= adjustZ;
	SetUseZBuffer3D(false);
	SetWriteZBuffer3D(false);
	 DrawBillboard3D(VPos, 0.5f, 0.0f, size, angle, handle, transFlag, ReverseXFlag, ReverseYFlag);
	 MyDraw::InitMyDraw();
}