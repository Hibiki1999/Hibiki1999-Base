#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include <map>
#include <memory>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>
#include <DxLib.h>

#include "../../Library/Screen/Screen.h"
#include "../../Library/Csv/CsvStruct.h"
#include "../../Library/Gamemanager/GameManager.h"
#include "../../GameObject/Parent/GameObject.h"
#include "../Image/Image.h"
#include "../../Library/Camera/Camera.h"

class Map
{
public:
	const bool spawnIsOval = false;//楕円の形で敵をスポーンしたいならtrueにしてください

	const int None = -1;
	const int Wall = 0;
	//ここでCellごとに定義

	GameManager& gm = GameManager::GetInstance();//中間、各オブジェクトの保存場所

	struct CellXY
	{
		int X = 0;
		int Y = 0;
		CellXY(int X, int Y) :X{ X }, Y{ Y } {};
		bool operator <(const CellXY& otherXY)const
		{
			if (Y < otherXY.Y)return true;
			if (Y > otherXY.Y)return false;
			if (X < otherXY.X)return true;
			if (X > otherXY.X)return false;
			return false;
		}
	};

	int spawnRangeX = 30;
	int spawnRangeY = 30;//敵が読み込まれる範囲
	std::map<CellXY, bool> SpawnDic;//連想配列、trueになったら出現

	const int CellSize = 32;

	float rotaGraphShiftX = CellSize / 2;
	float rotaGraphShiftY = CellSize / 2;//中心から描画するので、拡径の画像の中心を特定する

	CsvInt terrain;
	CsvInt enemyData;

	float positionX = 0;
	float positionY = 0;

	Map(float startPosition, std::string stageName)
	{
		positionX = startPosition;
		positionY = startPosition;//Csvデータの読み取り開始位置

		enemyData.Load(CellSize, "ResourceFile/MapFile/" + stageName + "_enemy.csv");
		terrain.Load(CellSize, "ResourceFile/MapFile/" + stageName + "_terrain.csv");

		Camera::MinCameraX = 0;
		Camera::MinCameraY = 0;
		Camera::MaxCameraX = CellSize * terrain.Width - Screen::Width;
		Camera::MaxCameraY = CellSize * terrain.Height - Screen::Height;//関数を渡す

		assert(spawnRangeX > 0 && spawnRangeY > 0);//敵出現射程を設定しなければ

		InitSpawnDic(spawnRangeX, spawnRangeY);//初期化
	}

	~Map()
	{
		enemyData.clear();
		terrain.clear();
	}

	void InitSpawnDic(int rangeCellX, int rangeCellY)
	{
		SpawnDic.clear();//一旦辞書をクリアするのでゲーム中の再設定も可(だが処理時間はかかる)
		// 敵出現射程の辞書初期化
		// ★ X = A cosθ Y = B sinθ(←楕円の方程式)
		// ★ 楕円の半径 r = √(A×A×cosθ×cosθ + B×B×sinθ×sinθ)
		// ★ xの2乗 + yの2乗 < rならば楕円の内側
		float A2 = (float)(rangeCellX * rangeCellX);
		float B2 = (float)(rangeCellY * rangeCellY);//2乗
		for (int x = -rangeCellX; x <= rangeCellX; x++)
		{
			for (int y = -rangeCellY; y <= rangeCellY; y++)
			{
				float theta = (float)std::atan2(y, x);//逆三角関数
				float cos_t = std::cos(theta);
				float sin_t = std::sin(theta);
				float r2 = A2 * cos_t + B2 * sin_t * sin_t;
				// ★ xの2乗 + yの2乗 < rならば楕円の内側
				//楕円の内側なら辞書SpawnDic[(x,y)] = true;として登録
				//【例】SpawnDic[(3,2)] = true;
				if (x * x + y * y <= r2) {}//SpawnDic[CellXY(x, y)] = true; 楕円の場合はこれを使って下の方をコメントアウト
				else SpawnDic[CellXY(x, y)] = true;	//【★四角形にしたいときはこちら】
			}
		}
	}

	float deltaSumX = 0;
	float deltaSumY = 0;

	void Scroll(float deltaX, float deltaY, std::shared_ptr<GameObject> baseObj = NULL)
	{
		bool isMoveCell = false;//移動しなければ実行しない
		deltaSumX = deltaX;
		deltaSumY = deltaY;
		if (deltaSumX <= -CellSize || CellSize <= deltaSumX
			|| deltaSumY <= -CellSize || CellSize <= deltaSumY)
		{
			isMoveCell = true;
		}

		if (isMoveCell)
		{
			float deltaMoveX = deltaSumX;
			float deltaMoveY = deltaSumY;//溜まった移動量を移動量deltaMoveとする
			int deltaCellX = (int)deltaMoveX / CellSize;
			int deltaCellY = (int)deltaMoveY / CellSize;//移動量をマス化

			if (deltaSumX <= -CellSize) deltaSumX += CellSize;
			else if (CellSize <= deltaSumX) deltaSumX -= CellSize;
			if (deltaSumY <= -CellSize) deltaSumY += CellSize;
			else if (CellSize <= deltaSumY) deltaSumY -= CellSize;//誤差調整

			int searchCount = 0;
			for (auto iter = SpawnDic.begin(); iter != SpawnDic.end(); iter++)
			{   //目標マス(iter)は射程マスかどうか 
				if (iter->second == true)//射程内であれば
				{
					CellXY xy = iter->first;//マスを登録

					int searchX = xy.X + deltaCellX;
					int searchY = xy.Y + deltaCellY;//登録したマスをXY分ける

					CellXY searchXY(searchX, searchY);//目標マスは登録済かを検索

					if (SpawnDic.count(searchXY) == 1)
					{
						if (SpawnDic[searchXY] == true) continue;//登録済であればスキップして次のマスに行く
					}

					int mapX = 0, mapY = 0;
					if (baseObj != NULL)
					{  // 基準となるオブジェクトがあるならその位置を基準に
						mapX = searchX + (int)(baseObj->vec2.x / CellSize);
						mapY = searchY + (int)(baseObj->vec2.y / CellSize);
					}
					else
					{  // 特に基準オブジェクトの指定がなければ現状ポジションを基準に
						mapX = searchX + (int)(positionX / CellSize);
						mapY = searchY + (int)(positionY / CellSize);
					}

					int objectID = -1;
					if (0 <= mapY && 0 <= mapX && mapY < enemyData.size() && mapX < enemyData[mapY].size())
					{
						objectID = enemyData[mapY][mapX];//データをアクセスできればIDを取得
						enemyData[mapY][mapX] = -1;//取得済みデータを消す
						if (objectID != -1)printfDx("newID %d(%d,%d)\n", objectID, mapX, mapY);//デバッグ用()画面に映る
					}
					SpawnObject(mapX, mapY, objectID);//マップデータを読み出し
				}
			}
		}
		positionX += deltaX;
		positionY += deltaY;
	}

	void SpawnObject(int mapX, int MapY, int objectID)
	{
		float spawnX = (float)(mapX * CellSize) + rotaGraphShiftX;
		float spawnY = (float)(MapY * CellSize) + rotaGraphShiftY;//生成位置を確定する

		if (objectID == -1) return;//この以下でID合わせて再生する者を追加する
		else if (objectID == 0) return;
		else assert("敵ID" + std::to_string(objectID) + "番の生成処理は未実装です" == "");//ここは再生する物のしめ
	}

	int GetTerrian(float worldX, float worldY)
	{
		if (worldX < 0 || worldY < 0) return None;//負の座標は無視

		int mapX = (int)(worldX / CellSize);
		int mapY = (int)(worldY / CellSize);

		if (mapX >= terrain.Width || mapY >= terrain.Height) return None;//範囲外も無視

		return terrain[mapY][mapX];//地形IDを取り出して返却
	}

	int SetTerrain(float worldX, float worldY, int Data)
	{
		if (worldX < 0 || worldY < 0) return None;//負の座標を無視

		int mapX = (int)(worldX / CellSize);
		int mapY = (int)(worldY / CellSize);

		if (mapX >= terrain.Width || mapY >= terrain.Height) return None;//範囲外も無視

		terrain[mapY][mapX] = Data;//データを更新

		return terrain[mapY][mapX];//入れる場所を返却
	}

	void DrawTerrain()
	{
		int left = (int)(Camera::x / CellSize);
		int top = (int)(Camera::y / CellSize);
		int right = (int)((Camera::x + Screen::Width - 1) / CellSize);
		int bottom = (int)((Camera::y + Screen::Height - 1) / CellSize);

		if (left < 0)left = 0;
		if (top < 0)top = 0;
		if (right >= terrain.Width)right = terrain.Width - 1;
		if (bottom >= terrain.Height)bottom = terrain.Height - 1;

		for (int cellX = left; cellX <= right; cellX++)
		{
			for (int cellY = top; cellY <= bottom; cellY++)
			{
				float x = (float)(cellX * CellSize) + rotaGraphShiftX;
				float y = (float)(cellY * CellSize) + rotaGraphShiftY;//位置を確定

				int id = -1;
				if (cellY < terrain.size() && cellX < terrain[cellY].size())//二次元配列範囲内のIDを読み取る
				{
					id = terrain[cellY][cellX];//二次元配列のデータを保存
				}

				Camera::DrawRotaGraphF(x, y, 1, 0, Image::mapChip.HandleArray[id]);//IDに従ってマップチップを描画
			}
		}
	}

	void DrawMouseSetTerrain(int worldX,int worldY,int id)//カーソルの位置に置き換えるマップチップを表示
	{
		if (worldX < 0 || worldY < 0) return;//負の座標を無視

		int mapX = (int)(worldX / CellSize);
		int mapY = (int)(worldY / CellSize);

		if (mapX >= terrain.Width || mapY >= terrain.Height) return;//範囲外も無視

		Camera::DrawRotaGraphF(worldX, worldY, 1, 0, Image::mapChip.HandleArray[id]);
	}

	bool isWall(float worldX, float worldY)
	{
		int terrainID = GetTerrian(worldX, worldY);

		return terrainID == Wall;
	}

};

#endif // !MAP_H_