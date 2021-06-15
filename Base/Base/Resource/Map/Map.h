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

	GameManager& gm = GameManager::GetInstance();//���ԁA�e�I�u�W�F�N�g�̕ۑ��ꏊ

	const bool spawnIsOval = false;//�ȉ~�̌`�œG���X�|�[���������Ȃ�true�ɂ��Ă�������

	const int None = -1;
	std::vector<int> Wall{ 0 };
	//������Cell���Ƃɒ�`


	int spawnRangeX = 30;
	int spawnRangeY = 30;//�G���ǂݍ��܂��͈�
	std::map<CellXY, bool> SpawnDic;//�A�z�z��Atrue�ɂȂ�����o��

	float rotaGraphShiftX = CellSize / 2.0f;
	float rotaGraphShiftY = CellSize / 2.0f;//���S����`�悷��̂ŁA�g�a�̉摜�̒��S����肷��

	float positionX = 0;
	float positionY = 0;

	float deltaSumX = 0;
	float deltaSumY = 0;

	void InitSpawnDic(int rangeCellX, int rangeCellY);

	void SpawnObject(int mapX, int MapY, int objectID);
};

#endif // !MAP_H_



//void DrawMouseSetTerrain(int worldX, int worldY, int id);//�J�[�\���̈ʒu�ɒu��������}�b�v�`�b�v��\��
//{
//	if (worldX < 0 || worldY < 0) return;//���̍��W�𖳎�

//	int mapX = (int)(worldX / CellSize);
//	int mapY = (int)(worldY / CellSize);

//	if (mapX >= terrain.Width || mapY >= terrain.Height) return;//�͈͊O������

//	//Camera::DrawRotaGraphF(worldX, worldY, 1, 0, Image::mapChip.HandleArray[id]);
//}