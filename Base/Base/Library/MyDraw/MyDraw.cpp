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

	//サイコロの6面を描く
	DrawDivRotaGraphF3D(Plane::Y, xf, yf - (imageHeight / 2) + adjust_y_, zf, ExRate, Angle, divImage, id, TransFlag, ReverseXFlag, ReverseYFlag, ReverseZFlag);
	DrawDivRotaGraphF3D(Plane::Y, xf, yf + (imageHeight / 2) + adjust_y_, zf, ExRate, Angle, divImage, id, TransFlag, ReverseXFlag, ReverseYFlag, ReverseZFlag);
	// X方向の裏側は左右反転
	DrawDivRotaGraphF3D(Plane::X, xf - (imageWidth / 2), yf + adjust_y_, zf, ExRate, Angle, divImage, id, TransFlag, ReverseXFlag, ReverseYFlag, !ReverseZFlag);
	DrawDivRotaGraphF3D(Plane::X, xf + (imageWidth / 2), yf + adjust_y_, zf, ExRate, Angle, divImage, id, TransFlag, ReverseXFlag, ReverseYFlag, ReverseZFlag);
	DrawDivRotaGraphF3D(Plane::Z, xf, yf + adjust_y_, zf - (imageHeight / 2), ExRate, Angle, divImage, id, TransFlag, ReverseXFlag, ReverseYFlag, ReverseZFlag);
	// Z方向の裏側は左右反転
	DrawDivRotaGraphF3D(Plane::Z, xf, yf + adjust_y_, zf + (imageHeight / 2), ExRate, Angle, divImage, id, TransFlag, !ReverseXFlag, ReverseYFlag, ReverseZFlag);
	return;
}

int MyDraw::DrawDivRotaGraphF3D(Plane plane, float xf, float yf, float zf, double ExRate, Vec3 Angle, DivImage& divImage, int id, int TransFlag, int ReverseXFlag, int ReverseYFlag, int ReverseZFlag)
{
	// 遠すぎるものは描かないで即return
	//if (zf > farClipPlane) return -1;

	// 右手・左手系とY軸矢印の方向に従い座標を変換
	Vec3 COVERT_XYZ = Vec3(xf, yf, zf);
	float Xf = COVERT_XYZ.x, Yf = COVERT_XYZ.y, Zf = COVERT_XYZ.z;

	if (id < 0 && divImage.AllNum <= id) { assert("div画像id指定範囲外" == ""); return -1; }

	int imageWidth = divImage.XSize;
	int imageHeight = divImage.YSize;
	float u_X0 = 0.0F, v_Y0 = 0.0F; //点Vertex[0]のuとvの値
	float u_X3 = 1.0F, v_Y3 = 1.0F; //点Vertex[3]のuとvの値
	if (divImage.XNum > 1 || divImage.YNum > 1)
	{   // div分割画像の分割位置確定のため横uと縦vの値を計算
		int divX = id % divImage.XNum;//分割X列番号
		int divY = id / divImage.XNum;//分割Y行番号
		u_X0 = (float)divX / (float)(divImage.XNum);
		v_Y0 = (float)divY / (float)(divImage.YNum);
		u_X3 = (float)(divX + 1) / (float)(divImage.XNum);
		v_Y3 = (float)(divY + 1) / (float)(divImage.YNum);
	}



	// 【拡大縮小率ExRate】をかけて画像サイズを再計算
	imageWidth = (int)(imageWidth * ExRate);  // 拡大縮小した画像の幅
	imageHeight = (int)(imageHeight * ExRate);// 拡大縮小した画像の高さ
	float halfWidth = (float)(imageWidth / 2);//画像幅の1/2(先に計算し使いまわして処理削減)
	float halfHeight = (float)(imageHeight / 2);//画像高さの1/2(先に計算し使いまわして処理削減)
	//【テクスチャ反転処理】幅halfWidthと高さhalfHeightをマイナスにすることで反転
	// ★ReverseXFlagとIsReverseX_Texture両方反転は【反転の反転で=反転しない!】
	// 【反転の反転で=反転しない!】は★XOR【排他的論理和 ^ 演算子】
	if ((IsReverseX_Texture ^ (ReverseXFlag == TRUE))
		&& (plane == Plane::Y || plane == Plane::Z))
	{   // マイナス幅でテクスチャ反転
		halfWidth = -halfWidth;
	}
	if ((IsReverseY_Texture ^ (ReverseYFlag == TRUE))
		&& (plane == Plane::X || plane == Plane::Z))
	{   // マイナス幅でテクスチャ反転
		halfHeight = -halfHeight;
	}
	if (IsReverseZ_Texture ^ (ReverseZFlag == TRUE))
	{   // マイナス幅でテクスチャ反転
		if (plane == Plane::X) halfWidth = -halfWidth;
		if (plane == Plane::Y) halfHeight = -halfHeight;
	}

	// ★CGの【最小単位は三角形】2Dはドットの集合で描くが【CGは三角形の集合で描く】
	VERTEX_3D Vertex[6]; // ポリゴン２枚なので、頂点は６個(三角3点×2)

	// ★頂点情報のセット
	{   // Plane=X なら X平面に(Y,Z) = (yf,zf)中心に描画
		// Plane=Y なら Y平面に(X,Z) = (xf,zf)中心に描画
		// Plane=Z なら Z平面に(X,Y) = (xf,yf)中心に描画
		// 回転は以下リンク参照
		// https://dxlib.xsrv.jp/cgi/patiobbs/patio.cgi?mode=past&no=2749
		MATRIX TransformMatrix;
		// 回転( x, y, z軸回転の順に回転した後、座標移動行列により平行移動)
		// ★★MMultは行列の乗算【乗算した順にx軸回転→y軸回転→z軸回転→平行移動】
		//★【複数軸回転は頭が混乱するのでクォータニオンをつかうやり方もある】
		TransformMatrix = MGetRotX(Angle.x);
		TransformMatrix = MMult(TransformMatrix, MGetRotY(Angle.y));
		TransformMatrix = MMult(TransformMatrix, MGetRotZ(Angle.z));
		//★【座標移動行列により移動】
		TransformMatrix = MMult(TransformMatrix, MGetTranslate(DxLib::VGet(Xf, Yf, Zf)));

		if (plane == Plane::X)
		{   //座標固定平面→→→→→→→→→↓X平面指定
			Vertex[0].pos = VTransform(DxLib::VGet(0.0F, +halfHeight, -halfWidth), TransformMatrix);
			Vertex[1].pos = VTransform(DxLib::VGet(0.0F, +halfHeight, +halfWidth), TransformMatrix);
			Vertex[2].pos = VTransform(DxLib::VGet(0.0F, -halfHeight, -halfWidth), TransformMatrix);
			Vertex[3].pos = VTransform(DxLib::VGet(0.0F, -halfHeight, +halfWidth), TransformMatrix);
		}
		else if (plane == Plane::Y)
		{   //座標固定平面→→→→→→→→→→→→→→→→↓Y平面指定
			Vertex[0].pos = VTransform(DxLib::VGet(-halfWidth, 0.0F, +halfHeight), TransformMatrix);
			Vertex[1].pos = VTransform(DxLib::VGet(+halfWidth, 0.0F, +halfHeight), TransformMatrix);
			Vertex[2].pos = VTransform(DxLib::VGet(-halfWidth, 0.0F, -halfHeight), TransformMatrix);
			Vertex[3].pos = VTransform(DxLib::VGet(+halfWidth, 0.0F, -halfHeight), TransformMatrix);
		}
		else // if (plane == Plane::Z)
		{   //座標固定平面→→→→→→→→→→→→→→→→→→→→→→→→→↓Z平面指定
			Vertex[0].pos = VTransform(DxLib::VGet(-halfWidth, +halfHeight, 0.0F), TransformMatrix);
			Vertex[1].pos = VTransform(DxLib::VGet(+halfWidth, +halfHeight, 0.0F), TransformMatrix);
			Vertex[2].pos = VTransform(DxLib::VGet(-halfWidth, -halfHeight, 0.0F), TransformMatrix);
			Vertex[3].pos = VTransform(DxLib::VGet(+halfWidth, -halfHeight, 0.0F), TransformMatrix);
		}
		Vertex[4].pos = Vertex[2].pos; // 点2と点4は同じ位置
		Vertex[5].pos = Vertex[1].pos; // 点1と点5は同じ位置
		//↑点0 点1&5 点4&2 点3 の4点の四角形を描く

		// ★div分割画像を考慮に入れて【UV展開】切り出し位置を0.0～1.0で指定
		Vertex[0].u = u_X0; Vertex[0].v = v_Y0;
		Vertex[1].u = u_X3; Vertex[1].v = v_Y0;
		Vertex[2].u = u_X0; Vertex[2].v = v_Y3;
		Vertex[3].u = u_X3; Vertex[3].v = v_Y3;
		Vertex[4].u = u_X0; Vertex[4].v = v_Y3;
		Vertex[5].u = u_X3; Vertex[5].v = v_Y0;

		// 輝度(明るさ)は全地点100%
		Vertex[0].r = Vertex[0].g = Vertex[0].b = 255;
		Vertex[1].r = Vertex[1].g = Vertex[1].b = 255;
		Vertex[2].r = Vertex[2].g = Vertex[2].b = 255;
		Vertex[3].r = Vertex[3].g = Vertex[3].b = 255;
		Vertex[4].r = Vertex[4].g = Vertex[4].b = 255;
		Vertex[5].r = Vertex[5].g = Vertex[5].b = 255;

		// a(アルファ不透明度) も最大値(255=不透明 0=透明)
		Vertex[0].a = 255; Vertex[1].a = 255;
		Vertex[2].a = 255;
		Vertex[5].a = 255;
		Vertex[4].a = 255; Vertex[3].a = 255;
		//↑上の順の点で点0 点1&5 点4&2 点3 の4点の四角形を描く
	}

	// ポリゴンを２枚描画
	return DrawPolygon3D(Vertex, 2, divImage.HandleArray[id], TransFlag);
}

int MyDraw::DrawDivRotaFloorF3D(Plane plane, float xf, float yf, float zf, double ExRate, double Angle, DivImage& divImage, int id, int TransFlag, int ReverseXFlag, int ReverseYFlag, int ReverseZFlag)
{
	Vec3 AngleVec = VecAngle(plane, Angle);
	int imageHeight = divImage.YSize;
	//                                              角度だけ↓VECTOR化
	return DrawDivRotaGraphF3D(plane, xf, yf - imageHeight / 2, zf, ExRate, AngleVec, divImage, id, TransFlag, ReverseXFlag, ReverseYFlag, ReverseZFlag);
}

int MyDraw::DrawRotaGraphF3D(Plane plane, float xf, float yf, float zf, double ExRate, Vec3 Angle, int GrHandle, int TransFlag, int ReverseXFlag, int ReverseYFlag, int ReverseZFlag)
{   // 1×1の単一画像としてGrHandleを引き継ぎ
	int imageWidth, imageHeight;
	GetGraphSize(GrHandle, &imageWidth, &imageHeight);
	DivImage divImage{ 1,1,imageWidth,imageHeight };
	divImage.HandleArray[0] = GrHandle;
	return DrawDivRotaGraphF3D(plane, xf, yf, zf, ExRate, Angle, divImage, 0, TransFlag, ReverseXFlag, ReverseYFlag, ReverseZFlag);
}   // ↓すぐ下のdiv対応版関数に引き継ぐ

Vec3 MyDraw::VGet(float x, float y, float z)
{   // DXライブラリの3D描画座標系に変換
	if (XYZ_ARROW.x == 1 && XYZ_ARROW.y == 1 && XYZ_ARROW.z == 1)
	{   // DX デフォルト2D描画座標系
		return VGet(x, y, z);
	}
	else if (XYZ_ARROW.x == 1 && XYZ_ARROW.y == -1 && XYZ_ARROW.z == 1)
	{   // DX 3D描画座標系
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
	// 平面に合わせて回転軸を選択
	if (plane == Plane::X) AngleVec.x = (float)Angle;
	else if (plane == Plane::Y) AngleVec.y = (float)Angle;
	else if (plane == Plane::Z) AngleVec.z = (float)Angle;

	return AngleVec;
}

void MyDraw::DrawPlaneCharaRotaGraphF3D(Vec3 position, double EXRate, double Angle, int handle, int TransFlag)
{   // 保存された板キャラの角度を使い板ポリゴンがカメラに面を向けるようにする
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