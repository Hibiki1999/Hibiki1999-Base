#ifndef MYMATH_H_
#define MYMATH_H_

#include <memory>

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
/// <param name="top1">   四角1の上端</param>
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

}; // 【注意】セミコロン抜けで【宣言が必要ですエラー】

#endif // 【宣言が必要ですエラーは上のセミコロン抜け】