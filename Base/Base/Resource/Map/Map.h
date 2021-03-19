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
	const bool spawnIsOval = false;//�ȉ~�̌`�œG���X�|�[���������Ȃ�true�ɂ��Ă�������

	const int None = -1;
	const int Wall = 0;
	//������Cell���Ƃɒ�`

	GameManager& gm = GameManager::GetInstance();//���ԁA�e�I�u�W�F�N�g�̕ۑ��ꏊ

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
	int spawnRangeY = 30;//�G���ǂݍ��܂��͈�
	std::map<CellXY, bool> SpawnDic;//�A�z�z��Atrue�ɂȂ�����o��

	const int CellSize = 32;

	float rotaGraphShiftX = CellSize / 2;
	float rotaGraphShiftY = CellSize / 2;//���S����`�悷��̂ŁA�g�a�̉摜�̒��S����肷��

	CsvInt terrain;
	CsvInt enemyData;

	float positionX = 0;
	float positionY = 0;

	Map(float startPosition, std::string stageName)
	{
		positionX = startPosition;
		positionY = startPosition;//Csv�f�[�^�̓ǂݎ��J�n�ʒu

		enemyData.Load(CellSize, "ResourceFile/MapFile/" + stageName + "_enemy.csv");
		terrain.Load(CellSize, "ResourceFile/MapFile/" + stageName + "_terrain.csv");

		Camera::MinCameraX = 0;
		Camera::MinCameraY = 0;
		Camera::MaxCameraX = CellSize * terrain.Width - Screen::Width;
		Camera::MaxCameraY = CellSize * terrain.Height - Screen::Height;//�֐���n��

		assert(spawnRangeX > 0 && spawnRangeY > 0);//�G�o���˒���ݒ肵�Ȃ����

		InitSpawnDic(spawnRangeX, spawnRangeY);//������
	}

	~Map()
	{
		enemyData.clear();
		terrain.clear();
	}

	void InitSpawnDic(int rangeCellX, int rangeCellY)
	{
		SpawnDic.clear();//��U�������N���A����̂ŃQ�[�����̍Đݒ����(�����������Ԃ͂�����)
		// �G�o���˒��̎���������
		// �� X = A cos�� Y = B sin��(���ȉ~�̕�����)
		// �� �ȉ~�̔��a r = ��(A�~A�~cos�Ɓ~cos�� + B�~B�~sin�Ɓ~sin��)
		// �� x��2�� + y��2�� < r�Ȃ�Αȉ~�̓���
		float A2 = (float)(rangeCellX * rangeCellX);
		float B2 = (float)(rangeCellY * rangeCellY);//2��
		for (int x = -rangeCellX; x <= rangeCellX; x++)
		{
			for (int y = -rangeCellY; y <= rangeCellY; y++)
			{
				float theta = (float)std::atan2(y, x);//�t�O�p�֐�
				float cos_t = std::cos(theta);
				float sin_t = std::sin(theta);
				float r2 = A2 * cos_t + B2 * sin_t * sin_t;
				// �� x��2�� + y��2�� < r�Ȃ�Αȉ~�̓���
				//�ȉ~�̓����Ȃ玫��SpawnDic[(x,y)] = true;�Ƃ��ēo�^
				//�y��zSpawnDic[(3,2)] = true;
				if (x * x + y * y <= r2) {}//SpawnDic[CellXY(x, y)] = true; �ȉ~�̏ꍇ�͂�����g���ĉ��̕����R�����g�A�E�g
				else SpawnDic[CellXY(x, y)] = true;	//�y���l�p�`�ɂ������Ƃ��͂�����z
			}
		}
	}

	float deltaSumX = 0;
	float deltaSumY = 0;

	void Scroll(float deltaX, float deltaY, std::shared_ptr<GameObject> baseObj = NULL)
	{
		bool isMoveCell = false;//�ړ����Ȃ���Ύ��s���Ȃ�
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
			float deltaMoveY = deltaSumY;//���܂����ړ��ʂ��ړ���deltaMove�Ƃ���
			int deltaCellX = (int)deltaMoveX / CellSize;
			int deltaCellY = (int)deltaMoveY / CellSize;//�ړ��ʂ��}�X��

			if (deltaSumX <= -CellSize) deltaSumX += CellSize;
			else if (CellSize <= deltaSumX) deltaSumX -= CellSize;
			if (deltaSumY <= -CellSize) deltaSumY += CellSize;
			else if (CellSize <= deltaSumY) deltaSumY -= CellSize;//�덷����

			int searchCount = 0;
			for (auto iter = SpawnDic.begin(); iter != SpawnDic.end(); iter++)
			{   //�ڕW�}�X(iter)�͎˒��}�X���ǂ��� 
				if (iter->second == true)//�˒����ł����
				{
					CellXY xy = iter->first;//�}�X��o�^

					int searchX = xy.X + deltaCellX;
					int searchY = xy.Y + deltaCellY;//�o�^�����}�X��XY������

					CellXY searchXY(searchX, searchY);//�ڕW�}�X�͓o�^�ς�������

					if (SpawnDic.count(searchXY) == 1)
					{
						if (SpawnDic[searchXY] == true) continue;//�o�^�ςł���΃X�L�b�v���Ď��̃}�X�ɍs��
					}

					int mapX = 0, mapY = 0;
					if (baseObj != NULL)
					{  // ��ƂȂ�I�u�W�F�N�g������Ȃ炻�̈ʒu�����
						mapX = searchX + (int)(baseObj->vec2.x / CellSize);
						mapY = searchY + (int)(baseObj->vec2.y / CellSize);
					}
					else
					{  // ���Ɋ�I�u�W�F�N�g�̎w�肪�Ȃ���Ό���|�W�V���������
						mapX = searchX + (int)(positionX / CellSize);
						mapY = searchY + (int)(positionY / CellSize);
					}

					int objectID = -1;
					if (0 <= mapY && 0 <= mapX && mapY < enemyData.size() && mapX < enemyData[mapY].size())
					{
						objectID = enemyData[mapY][mapX];//�f�[�^���A�N�Z�X�ł����ID���擾
						enemyData[mapY][mapX] = -1;//�擾�ς݃f�[�^������
						if (objectID != -1)printfDx("newID %d(%d,%d)\n", objectID, mapX, mapY);//�f�o�b�O�p()��ʂɉf��
					}
					SpawnObject(mapX, mapY, objectID);//�}�b�v�f�[�^��ǂݏo��
				}
			}
		}
		positionX += deltaX;
		positionY += deltaY;
	}

	void SpawnObject(int mapX, int MapY, int objectID)
	{
		float spawnX = (float)(mapX * CellSize) + rotaGraphShiftX;
		float spawnY = (float)(MapY * CellSize) + rotaGraphShiftY;//�����ʒu���m�肷��

		if (objectID == -1) return;//���̈ȉ���ID���킹�čĐ�����҂�ǉ�����
		else if (objectID == 0) return;
		else assert("�GID" + std::to_string(objectID) + "�Ԃ̐��������͖������ł�" == "");//�����͍Đ����镨�̂���
	}

	int GetTerrian(float worldX, float worldY)
	{
		if (worldX < 0 || worldY < 0) return None;//���̍��W�͖���

		int mapX = (int)(worldX / CellSize);
		int mapY = (int)(worldY / CellSize);

		if (mapX >= terrain.Width || mapY >= terrain.Height) return None;//�͈͊O������

		return terrain[mapY][mapX];//�n�`ID�����o���ĕԋp
	}

	int SetTerrain(float worldX, float worldY, int Data)
	{
		if (worldX < 0 || worldY < 0) return None;//���̍��W�𖳎�

		int mapX = (int)(worldX / CellSize);
		int mapY = (int)(worldY / CellSize);

		if (mapX >= terrain.Width || mapY >= terrain.Height) return None;//�͈͊O������

		terrain[mapY][mapX] = Data;//�f�[�^���X�V

		return terrain[mapY][mapX];//�����ꏊ��ԋp
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
				float y = (float)(cellY * CellSize) + rotaGraphShiftY;//�ʒu���m��

				int id = -1;
				if (cellY < terrain.size() && cellX < terrain[cellY].size())//�񎟌��z��͈͓���ID��ǂݎ��
				{
					id = terrain[cellY][cellX];//�񎟌��z��̃f�[�^��ۑ�
				}

				Camera::DrawRotaGraphF(x, y, 1, 0, Image::mapChip.HandleArray[id]);//ID�ɏ]���ă}�b�v�`�b�v��`��
			}
		}
	}

	void DrawMouseSetTerrain(int worldX,int worldY,int id)//�J�[�\���̈ʒu�ɒu��������}�b�v�`�b�v��\��
	{
		if (worldX < 0 || worldY < 0) return;//���̍��W�𖳎�

		int mapX = (int)(worldX / CellSize);
		int mapY = (int)(worldY / CellSize);

		if (mapX >= terrain.Width || mapY >= terrain.Height) return;//�͈͊O������

		Camera::DrawRotaGraphF(worldX, worldY, 1, 0, Image::mapChip.HandleArray[id]);
	}

	bool isWall(float worldX, float worldY)
	{
		int terrainID = GetTerrian(worldX, worldY);

		return terrainID == Wall;
	}

};

#endif // !MAP_H_