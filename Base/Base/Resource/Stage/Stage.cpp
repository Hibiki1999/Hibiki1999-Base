#include "Stage.h"
#include "../../Library/MyDraw/MyDraw.h"
#include "../../GameObject/Parent/GameObject.h"

#include <DxLib.h>

constexpr int HitDimNum = 1;
constexpr int Max_Hitcoll = 256;
constexpr int Hit_TryNum = 16;

Stage::Stage(std::string stageName)
{
	std::string path = "ResourceFile/StageFile/" + stageName;
	this->model_ = MV1LoadModel(path.c_str());
	transform_.position(Vec3(0, 0, 0));
	transform_.rotation(Quaternion(0, 0, 0));
	transform_.scale(Vec3(0, 0, 0));
}

Stage::~Stage()
{
}

Vec3 Stage::check_colli(std::shared_ptr<GameObject> obj)
{
	Vec3 position = obj->transform().position();
	Vec3 velo = obj->velocity() + obj->gravity_velo();
	float radius = obj->collider().GetRadius();
	float height = obj->height();
	bool isAir = obj->isAir();


	MV1_COLL_RESULT_POLY_DIM HitDim;			// プレイヤーの周囲にあるポリゴンを検出した結果が代入される当たり判定結果構造体
	HitDim = MV1CollCheck_Sphere(model_, -1, position + velo, 500.0f + velo.Length());

	bool MoveFlag = velo.NotZero() ? true : false;

	int KabeNum = 0;
	int YukaNum = 0;
	int HitFlag = 0;
	MV1_COLL_RESULT_POLY* Kabe[Max_Hitcoll];	// 壁ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
	MV1_COLL_RESULT_POLY* Yuka[Max_Hitcoll];	// 床ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
	MV1_COLL_RESULT_POLY* Poly;				// ポリゴンの構造体にアクセスするために使用するポインタ( 使わなくても済ませられますがプログラムが長くなるので・・・ )
	HITRESULT_LINE LineRes;				// 線分とポリゴンとの当たり判定の結果を代入する構造体
	Vec3 OldPos;
	Vec3 NowPos;

	OldPos = position - velo;
	NowPos = position;

	for (int i = 0; i < HitDim.HitNum; i++) {

		if (HitDim.Dim[i].Normal.y<0.000001f && HitDim.Dim[i].Normal.y > -0.000001f) {
			// 壁ポリゴンと判断された場合でも、プレイヤーのＹ座標＋１．０ｆより高いポリゴンのみ当たり判定を行う
			if (HitDim.Dim[i].Position[0].y > OldPos.y + 1.0f ||
				HitDim.Dim[i].Position[1].y > OldPos.y + 1.0f ||
				HitDim.Dim[i].Position[2].y > OldPos.y + 1.0f)
			{
				// ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加
				if (KabeNum < Max_Hitcoll)
				{
					// ポリゴンの構造体のアドレスを壁ポリゴンポインタ配列に保存する
					Kabe[KabeNum] = &HitDim.Dim[i];

					// 壁ポリゴンの数を加算する
					KabeNum++;
				}
			}
		}
		else
		{
			// ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加
			if (YukaNum < Max_Hitcoll)
			{
				// ポリゴンの構造体のアドレスを床ポリゴンポインタ配列に保存する
				Yuka[YukaNum] = &HitDim.Dim[i];

				// 床ポリゴンの数を加算する
				YukaNum++;
			}
		}

	}

	if (KabeNum != 0) {
		HitFlag = 0;

		if (MoveFlag) {
			// 壁ポリゴンの数だけ繰り返し
			for (int i = 0; i < KabeNum; i++)
			{
				// i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
				Poly = Kabe[i];

				// ポリゴンとプレイヤーが当たっていなかったら次のカウントへ
				if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, height, 0.0f)), radius, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) continue;

				// ここにきたらポリゴンとプレイヤーが当たっているということなので、ポリゴンに当たったフラグを立てる
				HitFlag = 1;

				// 壁に当たったら壁に遮られない移動成分分だけ移動する
				{
					VECTOR SlideVec;	// プレイヤーをスライドさせるベクトル

					// 進行方向ベクトルと壁ポリゴンの法線ベクトルに垂直なベクトルを算出
					SlideVec = VCross(velo, Poly->Normal);

					// 算出したベクトルと壁ポリゴンの法線ベクトルに垂直なベクトルを算出、これが
					// 元の移動成分から壁方向の移動成分を抜いたベクトル
					SlideVec = VCross(Poly->Normal, SlideVec);

					// それを移動前の座標に足したものを新たな座標とする
					NowPos = VAdd(OldPos, SlideVec);
				}
				int j = 0;
				// 新たな移動座標で壁ポリゴンと当たっていないかどうかを判定する
				for (j = 0; j < KabeNum; j++)
				{
					// j番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
					Poly = Kabe[j];

					// 当たっていたらループから抜ける
					if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, height, 0.0f)), radius, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE) break;
				}

				// j が KabeNum だった場合はどのポリゴンとも当たらなかったということなので
				// 壁に当たったフラグを倒した上でループから抜ける
				if (j == KabeNum)
				{
					HitFlag = 0;
					break;
				}
			}
		}
		else
		{
			// 移動していない場合の処理

			// 壁ポリゴンの数だけ繰り返し
			for (int i = 0; i < KabeNum; i++)
			{
				// i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
				Poly = Kabe[i];

				// ポリゴンに当たっていたら当たったフラグを立てた上でループから抜ける
				if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, height, 0.0f)), radius, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE)
				{
					HitFlag = 1;
					break;
				}
			}
		}

		// 壁に当たっていたら壁から押し出す処理を行う
		if (HitFlag == 1)
		{
			// 壁からの押し出し処理を試みる最大数だけ繰り返し
			for (int k = 0; k < Hit_TryNum; k++)
			{
				int i = 0;
				// 壁ポリゴンの数だけ繰り返し
				for (i = 0; i < KabeNum; i++)
				{
					// i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
					Poly = Kabe[i];

					// プレイヤーと当たっているかを判定
					if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, height, 0.0f)), radius, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) continue;

					// 当たっていたら規定距離分プレイヤーを壁の法線方向に移動させる
					NowPos = VAdd(NowPos, VScale(Poly->Normal, 5.0f));

					int j = 0;
					// 移動した上で壁ポリゴンと接触しているかどうかを判定
					for (j = 0; j < KabeNum; j++)
					{
						// 当たっていたらループを抜ける
						Poly = Kabe[j];
						if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, height, 0.0f)), radius, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE) break;
					}

					// 全てのポリゴンと当たっていなかったらここでループ終了
					if (j == KabeNum) break;
				}

				// i が KabeNum ではない場合は全部のポリゴンで押し出しを試みる前に全ての壁ポリゴンと接触しなくなったということなのでループから抜ける
				if (i != KabeNum) break;
			}
		}
	}

	// 床ポリゴンとの当たり判定
	if (YukaNum != 0)
	{
		// ジャンプ中且つ上昇中の場合は処理を分岐
		if (velo.y > 0)
		{
			float MinY;

			// 天井に頭をぶつける処理を行う

			// 一番低い天井にぶつける為の判定用変数を初期化
			MinY = 0.0f;

			// 当たったかどうかのフラグを当たっていないを意味する０にしておく
			HitFlag = 0;

			// 床ポリゴンの数だけ繰り返し
			for (int i = 0; i < YukaNum; i++)
			{
				// i番目の床ポリゴンのアドレスを床ポリゴンポインタ配列から取得
				Poly = Yuka[i];

				// 足先から頭の高さまでの間でポリゴンと接触しているかどうかを判定
				LineRes = HitCheck_Line_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, height, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);

				// 接触していなかったら何もしない
				if (LineRes.HitFlag == FALSE) continue;

				// 既にポリゴンに当たっていて、且つ今まで検出した天井ポリゴンより高い場合は何もしない
				if (HitFlag == 1 && MinY < LineRes.Position.y) continue;

				// ポリゴンに当たったフラグを立てる
				HitFlag = 1;

				// 接触したＹ座標を保存する
				MinY = LineRes.Position.y;
			}

			// 接触したポリゴンがあったかどうかで処理を分岐
			if (HitFlag == 1)
			{
				// 接触した場合はプレイヤーのＹ座標を接触座標を元に更新
				NowPos.y = MinY - height;

				// Ｙ軸方向の速度は反転
				obj->minus_gravity_velo();
			}
		}
		else
		{
			float MaxY;

			// 下降中かジャンプ中ではない場合の処理

			// 床ポリゴンに当たったかどうかのフラグを倒しておく
			HitFlag = 0;

			// 一番高い床ポリゴンにぶつける為の判定用変数を初期化
			MaxY = 0.0f;

			// 床ポリゴンの数だけ繰り返し
			for (int i = 0; i < YukaNum; i++)
			{
				// i番目の床ポリゴンのアドレスを床ポリゴンポインタ配列から取得
				Poly = Yuka[i];

				// ジャンプ中かどうかで処理を分岐
				if (isAir)
				{
					// ジャンプ中の場合は頭の先から足先より少し低い位置の間で当たっているかを判定
					LineRes = HitCheck_Line_Triangle(VAdd(NowPos, VGet(0.0f, height, 0.0f)), VAdd(NowPos, VGet(0.0f, -1.0f, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);
				}
				else
				{
					//走っている場合は頭の先からそこそこ低い位置の間で当たっているかを判定( 傾斜で落下状態に移行してしまわない為 )
					LineRes = HitCheck_Line_Triangle(VAdd(NowPos, VGet(0.0f, height, 0.0f)), VAdd(NowPos, VGet(0.0f, -40.0f, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);
				}

				// 当たっていなかったら何もしない
				if (LineRes.HitFlag == FALSE) continue;

				// 既に当たったポリゴンがあり、且つ今まで検出した床ポリゴンより低い場合は何もしない
				if (HitFlag == 1 && MaxY > LineRes.Position.y) continue;

				// ポリゴンに当たったフラグを立てる
				HitFlag = 1;

				// 接触したＹ座標を保存する
				MaxY = LineRes.Position.y;
			}

			// 床ポリゴンに当たったかどうかで処理を分岐
			if (HitFlag == 1)
			{
				// 当たった場合

				// 接触したポリゴンで一番高いＹ座標をプレイヤーのＹ座標にする
				NowPos.y = MaxY;
				obj->grounded();
				// Ｙ軸方向の移動速度は０に
				//pl.JumpPower = 0.0f;

			//	// もしジャンプ中だった場合は着地状態にする
			//	if (pl.State == 2)
			//	{
			//		// 移動していたかどうかで着地後の状態と再生するアニメーションを分岐する
			//		if (MoveFlag)
			//		{
			//			// 移動している場合は走り状態に
			//			Player_PlayAnim(1);
			//			pl.State = 1;
			//		}
			//		else
			//		{
			//			// 移動していない場合は立ち止り状態に
			//			Player_PlayAnim(4);
			//			pl.State = 0;
			//		}

			//		// 着地時はアニメーションのブレンドは行わない
			//		pl.AnimBlendRate = 1.0f;
			//	}
			//}
			//else
			//{
			//	// 床コリジョンに当たっていなくて且つジャンプ状態ではなかった場合は
			//	if (pl.State != 2)
			//	{
			//		// ジャンプ中にする
			//		pl.State = 2;

			//		// ちょっとだけジャンプする
			//		pl.JumpPower = PLAYER_FALL_UP_POWER;

			//		// アニメーションは落下中のものにする
			//		Player_PlayAnim(3);
			//	}
			//}
			}
		}
	}

	MV1CollResultPolyDimTerminate(HitDim);
	return NowPos;
}

void Stage::draw() const
{
	MyDraw::Draw3DModel(model_, transform_);

	//Vec3 objPos;


















}
