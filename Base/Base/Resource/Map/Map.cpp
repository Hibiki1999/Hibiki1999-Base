#include "Map.h"

Map::Map(float startPosition, std::string stageName)
{
	positionX = startPosition;
	positionY = startPosition;//Csv�f�[�^�̓ǂݎ��J�n�ʒu

	enemyData.Load(CellSize, "ResourceFile/MapFile/" + stageName + "_enemy.csv");
	terrain.Load(CellSize, "ResourceFile/MapFile/" + stageName + "_terrain.csv");

	assert(spawnRangeX > 0 && spawnRangeY > 0);//�G�o���˒���ݒ肵�Ȃ����

	InitSpawnDic(spawnRangeX, spawnRangeY);//������
}

Map::~Map()
{
	enemyData.clear();
	terrain.clear();
}

void Map::InitSpawnDic(int rangeCellX, int rangeCellY)

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

void Map::Scroll(float deltaX, float deltaY, std::shared_ptr<GameObject> baseObj)
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
					mapX = searchX + (int)(baseObj->transform().position().x / CellSize);
					mapY = searchY + (int)(baseObj->transform().position().y / CellSize);
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

void Map::SpawnObject(int mapX, int MapY, int objectID)
{
	float spawnX = (float)(mapX * CellSize) + rotaGraphShiftX;
	float spawnY = (float)(MapY * CellSize) + rotaGraphShiftY;//�����ʒu���m�肷��

	if (objectID == -1) return;//���̈ȉ���ID���킹�čĐ�����҂�ǉ�����
	else if (objectID == 0) return;
	else assert("�GID" + std::to_string(objectID) + "�Ԃ̐��������͖������ł�" == "");//�����͍Đ����镨�̂���
}

int Map::GetTerrian(float worldX, float worldY)
{
	if (worldX < 0 || worldY < 0) return None;//���̍��W�͖���

	int mapX = (int)(worldX / CellSize);
	int mapY = (int)(worldY / CellSize);

	if (mapX >= terrain.Width || mapY >= terrain.Height) return None;//�͈͊O������

	return terrain[mapY][mapX];//�n�`ID�����o���ĕԋp

}

int Map::SetTerrain(float worldX, float worldY, int Data)
{
	if (worldX < 0 || worldY < 0) return None;//���̍��W�𖳎�

	int mapX = (int)(worldX / CellSize);
	int mapY = (int)(worldY / CellSize);

	if (mapX >= terrain.Width || mapY >= terrain.Height) return None;//�͈͊O������

	terrain[mapY][mapX] = Data;//�f�[�^���X�V

	return terrain[mapY][mapX];//�����ꏊ��ԋp
}

void Map::DrawTerrain()
{
	for (int cellX = 0; cellX <= terrain.Width - 1; cellX++)
	{
		for (int cellY = 0; cellY <= terrain.Height; cellY++)
		{
			float x = (float)(cellX * CellSize) + rotaGraphShiftX;
			float y = (float)(cellY * CellSize) + rotaGraphShiftY;//�ʒu���m��

			int id = -1;
			if (cellY < terrain.size() && cellX < terrain[cellY].size())//�񎟌��z��͈͓���ID��ǂݎ��
			{
				id = terrain[cellY][cellX];//�񎟌��z��̃f�[�^��ۑ�
			}
			if (0 <= id && id < Image::mapChip.AllNum) {
				MyDraw::DrawDivRotaFloorF3D(Plane::Y, x, 0, y, 1.0f, 0, Image::mapChip, id);
				if (id == 0) {
					MyDraw::DrawDivRotaDivBoxF3D(x, -0, y, 1, MyDraw::VGet(0, 0, 0), Image::mapChip, id);
				}
			}

			//DrawRotaGraphF(x, y, 1, 0, Image::mapChip.HandleArray[id], 1);//ID�ɏ]���ă}�b�v�`�b�v��`��
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