#ifndef MYMATH_H_
#define MYMATH_H_

#include <memory>
#include <vector>

// 数学関連クラス
class MyMath
{
public:
	// C ++標準では、静的static定数の【整数型】または【列挙型】のみをクラス内で初期化できます。
	// これが、一部の初期化が許可されているのに他のstatic floatなどが初期化できない理由です。

	// 【OH,ノー】 float小数を定義するためだけにcppファイルを作成しないと
	//static const float Sqrt2 =【このイコールでエラー】 1.41421356237f; 
	// ルート2
	static const float Sqrt2; // = 1.41421356237f;

	static const float PI;// = 3.14159265359f;

	static const float Deg2Rad;//=PI/2;

	/// <summary>
	/// 円と円が重なっているかを調べる
	/// </summary>
	/// <param name="x1">円1の中心x</param>
	/// <param name="y1">円1の中心y</param>
	/// <param name="radius1">円1の半径</param>
	/// <param name="x2">円2の中心x</param>
	/// <param name="y2">円2の中心y</param>
	/// <param name="radius2">円2の半径</param>
	/// <returns>重なっていればtrue、重なっていなければfalseを返却する</returns>
	static bool CircleCircleIntersection(
		float x1, float y1, float radius1,
		float x2, float y2, float radius2)
	{
		return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))
			< ((radius1 + radius2) * (radius1 + radius2));
	}

	/// <summary>
	/// 四角と四角が重なっているかを調べる
	/// </summary>
	/// <param name="left1">  四角1の左端</param>
	/// <param name="right1"> 四角1の右端</param>
	///	 <param name="top1">   四角1の上端</param>
	/// <param name="bottom1">四角1の下端</param>
	/// <param name="left2">  四角2の左端</param>
	/// <param name="right2"> 四角2の右端</param>
	/// <param name="top2">   四角2の上端</param>
	/// <param name="bottom2">四角2の下端</param>
	/// <returns>重なっていればtrue、重なっていなければfalseを返却する</returns>
	static bool SquareSquareIntersection(float left1, float right1, float top1, float bottom1, float left2, float right2, float top2, float bottom2)
	{
		return ((left1 < right2) && (right1 > left2) && (top1 < bottom2) && (bottom1 > top2));
	}

	/// <summary>
	/// 円形と四角が重なっているかを調べる
	/// </summary>
	/// <param name="circle">円の座標</param>
	/// <param name="r">円の半径</param>
	/// <param name="leftTop">四角の左上(x,y)</param>
	/// <param name="rightBottom">四角の右下(x,y)</param>
	/// <returns>重なっていればtrue</returns>
	static bool CicleSquareIntersection(Vec2 circle, float r, Vec2 leftTop, Vec2 rightBottom)
	{
		bool a = ((circle.x > leftTop.x) && (circle.x < rightBottom.x) && (circle.y > (leftTop.y - r)) && (circle.y < (rightBottom.y + r)));
		bool b = ((circle.x > (leftTop.x - r)) && (circle.x < (rightBottom.x + r)) && (circle.y > leftTop.y) && (circle.y < rightBottom.y));
		bool c = (((leftTop.x - circle.x) * (leftTop.x - circle.x)) + ((leftTop.y - circle.y) * (leftTop.y - circle.y))) < (r * r);
		bool d = (((rightBottom.x - circle.x) * (rightBottom.x - circle.x)) + ((leftTop.y - circle.y) * (leftTop.y - circle.y))) < (r * r);
		bool e = (((rightBottom.x - circle.x) * (rightBottom.x - circle.x)) + ((rightBottom.y - circle.y) * (rightBottom.y - circle.y))) < (r * r);
		bool f = (((leftTop.x - circle.x) * (leftTop.x - circle.x)) + ((rightBottom.y - circle.y) * (rightBottom.y - circle.y))) < (r * r);

		if (a || b || c || d || e || f)return true;
		//=============================使用例==========================//
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
	/// 点から点への角度（ラジアン）を求める。
	/// </summary>
	/// <param name="fromX">始点x</param>
	/// <param name="fromY">始点y</param>
	/// <param name="toX">終点x</param>
	/// <param name="toY">終点y</param>
	/// <returns></returns>
	static float PointToPointAngle(float fromX, float fromY, float toX, float toY)
	{
		return (float)atan2((float)(toY - fromY), (float)(toX - fromX));
	}

	/// <summary>
	/// 点と点の距離を計算
	/// </summary>
	/// <param name="x1">点1のx</param>
	/// <param name="y1">点1のy</param>
	/// <param name="x2">点2のx</param>
	/// <param name="y2">点2のy</param>
	/// <returns></returns>
	static float VetorLenght(float x1, float y1, float x2, float y2)
	{
		x1 -= x2;
		y1 -= y2;
		float lenght;
		lenght = sqrtf(((x1 * x1) + (y2 * y2)));
		return lenght;
	}

}; // 【注意】セミコロン抜けで【宣言が必要ですエラー】

#endif // 【宣言が必要ですエラーは上のセミコロン抜け】