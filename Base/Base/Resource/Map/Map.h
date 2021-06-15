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

	Map(float startPosition, std::string stageName);

	~Map();

	void Scroll(float deltaX, float deltaY, std::shared_ptr<GameObject> baseObj = NULL);

	int GetTerrian(float worldX, float worldY);

	int SetTerrain(float worldX, float worldY, int Data);

	void DrawTerrain();

	bool isWall(float worldX, float worldY);

	CsvInt terrain;
	CsvInt enemyData;

	const int CellSize = 64;

private:

	GameManager& gm = GameManager::GetInstance();//中間、各オブジェクトの保存場所

	const bool spawnIsOval = false;//楕円の形で敵をスポーンしたいならtrueにしてください

	const int None = -1;
	std::vector<int> Wall{ 0 };
	//ここでCellごとに定義


	int spawnRangeX = 30;
	int spawnRangeY = 30;//敵が読み込まれる範囲
	std::map<CellXY, bool> SpawnDic;//連想配列、trueになったら出現

	float rotaGraphShiftX = CellSize / 2.0f;
	float rotaGraphShiftY = CellSize / 2.0f;//中心から描画するので、拡径の画像の中心を特定する

	float positionX = 0;
	float positionY = 0;

	float deltaSumX = 0;
	float deltaSumY = 0;

	void InitSpawnDic(int rangeCellX, int rangeCellY);

	void SpawnObject(int mapX, int MapY, int objectID);
};

#endif // !MAP_H_



//void DrawMouseSetTerrain(int worldX, int worldY, int id);//カーソルの位置に置き換えるマップチップを表示
//{
//	if (worldX < 0 || worldY < 0) return;//負の座標を無視

//	int mapX = (int)(worldX / CellSize);
//	int mapY = (int)(worldY / CellSize);

//	if (mapX >= terrain.Width || mapY >= terrain.Height) return;//範囲外も無視

//	//Camera::DrawRotaGraphF(worldX, worldY, 1, 0, Image::mapChip.HandleArray[id]);
//}