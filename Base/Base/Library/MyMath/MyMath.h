#ifndef MYMATH_H_
#define MYMATH_H_

#include <memory>
#include <vector>
#include "../Transform/Vec2/Vec2.h"

// ���w�֘A�N���X
class MyMath
{
public:
	// C ++�W���ł́A�ÓIstatic�萔�́y�����^�z�܂��́y�񋓌^�z�݂̂��N���X���ŏ������ł��܂��B
	// ���ꂪ�A�ꕔ�̏�������������Ă���̂ɑ���static float�Ȃǂ��������ł��Ȃ����R�ł��B

	// �yOH,�m�[�z float�������`���邽�߂�����cpp�t�@�C�����쐬���Ȃ���
	//static const float Sqrt2 =�y���̃C�R�[���ŃG���[�z 1.41421356237f; 
	// ���[�g2
	static const float Sqrt2; // = 1.41421356237f;

	static const float PI;// = 3.14159265359f;

	static const float Deg2Rad;//=PI/2;


	static float Square(float a);

	/// <summary>
	/// �~�Ɖ~���d�Ȃ��Ă��邩�𒲂ׂ�
	/// </summary>
	/// <param name="vec1">�~1</param>
	/// <param name="radius1">�~1�̔��a</param>
	/// <param name="vec2">�~2</param>
	/// <param name="radius2">�~2�̔��a</param>
	/// <returns></returns>
	static bool CircleCircleIntersection(Vec2 vec1, float radius1, Vec2 vec2, float radius2)
	{
		return (vec1.Vec2::distanceFrom(vec2) < (radius1 + radius2));
	}

	/// <summary>
	/// �l�p�Ǝl�p���d�Ȃ��Ă��邩�𒲂ׂ�
	/// </summary>
	/// <param name="left1">  �l�p1�̍��[</param>
	/// <param name="right1"> �l�p1�̉E�[</param>
	///	<param name="top1">   �l�p1�̏�[</param>
	/// <param name="bottom1">�l�p1�̉��[</param>
	/// <param name="left2">  �l�p2�̍��[</param>
	/// <param name="right2"> �l�p2�̉E�[</param>
	/// <param name="top2">   �l�p2�̏�[</param>
	/// <param name="bottom2">�l�p2�̉��[</param>
	/// <returns>�d�Ȃ��Ă����true�A�d�Ȃ��Ă��Ȃ����false��ԋp����</returns>
	static bool SquareSquareIntersection(float left1, float right1, float top1, float bottom1, float left2, float right2, float top2, float bottom2)
	{
		return ((left1 < right2) && (right1 > left2) && (top1 < bottom2) && (bottom1 > top2));
	}

	/// <summary>
	/// �~�`�Ǝl�p���d�Ȃ��Ă��邩�𒲂ׂ�
	/// </summary>
	/// <param name="circle">�~�̍��W</param>
	/// <param name="r">�~�̔��a</param>
	/// <param name="leftTop">�l�p�̍���(x,y)</param>
	/// <param name="rightBottom">�l�p�̉E��(x,y)</param>
	/// <returns>�d�Ȃ��Ă����true</returns>
	static bool CicleSquareIntersection(Vec2 circle, float r, Vec2 leftTop, Vec2 rightBottom)
	{
		bool a = ((circle.x > leftTop.x) && (circle.x < rightBottom.x) && (circle.y > (leftTop.y - r)) && (circle.y < (rightBottom.y + r)));
		bool b = ((circle.x > (leftTop.x - r)) && (circle.x < (rightBottom.x + r)) && (circle.y > leftTop.y) && (circle.y < rightBottom.y));
		bool c = (((leftTop.x - circle.x) * (leftTop.x - circle.x)) + ((leftTop.y - circle.y) * (leftTop.y - circle.y))) < (r * r);
		bool d = (((rightBottom.x - circle.x) * (rightBottom.x - circle.x)) + ((leftTop.y - circle.y) * (leftTop.y - circle.y))) < (r * r);
		bool e = (((rightBottom.x - circle.x) * (rightBottom.x - circle.x)) + ((rightBottom.y - circle.y) * (rightBottom.y - circle.y))) < (r * r);
		bool f = (((leftTop.x - circle.x) * (leftTop.x - circle.x)) + ((rightBottom.y - circle.y) * (rightBottom.y - circle.y))) < (r * r);

		if (a || b || c || d || e || f)return true;
		//=============================�g�p��==========================//
		//if (MyMath::CicleSquareIntersection(
		//		Vec2(gm.player->x, gm.player->y),
		//		gm.player->rotaGraphShiftX,
		//		Vec2(gm.tobject->GetLeft(), gm.tobject->GetTop()),
		//		Vec2(gm.tobject->GetRight(), gm.tobject->GetBottom())))
		//	{
		//	gm.player->OnCollisionSquare();
		//	}
		//===========================================================//
	}

	/// <summary>
	/// �_����_�ւ̊p�x�i���W�A���j�����߂�B
	/// </summary>
	/// <param name="fromX">�n�_x</param>
	/// <param name="fromY">�n�_y</param>
	/// <param name="toX">�I�_x</param>
	/// <param name="toY">�I�_y</param>
	/// <returns></returns>
	static float PointToPointAngle(float fromX, float fromY, float toX, float toY)
	{
		return (float)atan2((float)(toY - fromY), (float)(toX - fromX));
	}

}; // �y���Ӂz�Z�~�R���������Ły�錾���K�v�ł��G���[�z

#endif // �y�錾���K�v�ł��G���[�͏�̃Z�~�R���������z