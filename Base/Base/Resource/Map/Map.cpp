#include "Map.h"

Map::Map(float startPosition, std::string stageName)
{
	positionX = startPosition;
	positionY = startPosition;//Csvデータの読み取り開始位置

	enemyData.Load(CellSize, "ResourceFile/MapFile/" + stageName + "_enemy.csv");
	terrain.Load(CellSize, "ResourceFile/MapFile/" + stageName + "_terrain.csv");

	assert(spawnRangeX > 0 && spawnRangeY > 0);//敵出現射程を設定しなければ

	InitSpawnDic(spawnRangeX, spawnRangeY);//初期化
}

Map::~Map()
{
	enemyData.clear();
	terrain.clear();
}

void Map::InitSpawnDic(int rangeCellX, int rangeCellY)

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

void Map::Scroll(float deltaX, float deltaY, std::shared_ptr<GameObject> baseObj)
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
					mapX = searchX + (int)(baseObj->transform().position().x / CellSize);
					mapY = searchY + (int)(baseObj->transform().position().y / CellSize);
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

void Map::SpawnObject(int mapX, int MapY, int objectID)
{
	float spawnX = (float)(mapX * CellSize) + rotaGraphShiftX;
	float spawnY = (float)(MapY * CellSize) + rotaGraphShiftY;//生成位置を確定する

	if (objectID == -1) return;//この以下でID合わせて再生する者を追加する
	else if (objectID == 0) return;
	else assert("敵ID" + std::to_string(objectID) + "番の生成処理は未実装です" == "");//ここは再生する物のしめ
}

int Map::GetTerrian(float worldX, float worldY)
{
	if (worldX < 0 || worldY < 0) return None;//負の座標は無視

	int mapX = (int)(worldX / CellSize);
	int mapY = (int)(worldY / CellSize);

	if (mapX >= terrain.Width || mapY >= terrain.Height) return None;//範囲外も無視

	return terrain[mapY][mapX];//地形IDを取り出して返却

}

int Map::SetTerrain(float worldX, float worldY, int Data)
{
	if (worldX < 0 || worldY < 0) return None;//負の座標を無視

	int mapX = (int)(worldX / CellSize);
	int mapY = (int)(worldY / CellSize);

	if (mapX >= terrain.Width || mapY >= terrain.Height) return None;//範囲外も無視

	terrain[mapY][mapX] = Data;//データを更新

	return terrain[mapY][mapX];//入れる場所を返却
}

void Map::DrawTerrain()
{
	for (int cellX = 0; cellX <= terrain.Width - 1; cellX++)
	{
		for (int cellY = 0; cellY <= terrain.Height; cellY++)
		{
			float x = (float)(cellX * CellSize) + rotaGraphShiftX;
			float y = (float)(cellY * CellSize) + rotaGraphShiftY;//位置を確定

			int id = -1;
			if (cellY < terrain.size() && cellX < terrain[cellY].size())//二次元配列範囲内のIDを読み取る
			{
				id = terrain[cellY][cellX];//二次元配列のデータを保存
			}
			if (0 <= id && id < Image::mapChip.AllNum) {
				MyDraw::DrawDivRotaFloorF3D(Plane::Y, x, 0, y, 1.0, 0, Image::mapChip, id);
				if (id == 0) {
					MyDraw::DrawDivRotaDivBoxF3D(x, -0, y, 1.0, MyDraw::VGet(0, 0, 0), Image::mapChip, id);
				}
			}

			//DrawRotaGraphF(x, y, 1, 0, Image::mapChip.HandleArray[id], 1);//IDに従ってマップチップを描画
		}
	}
}

bool Map::isWall(float worldX, float worldY)
{
	int terrainID = GetTerrian(worldX, worldY);

	for (auto i : Wall) {
		return terrainID == i;

	}
	return false;
}