#include "Image.h"
#include <string>

DivImage Image::mapChip{ 16, 16, 32, 32 };//X�̐��AY�̐��AX�̃T�C�Y�AY�̃T�C�Y
DivImage Image::Explo{ 10, 1,256, 256 };//X�̐��AY�̐��AX�̃T�C�Y�AY�̃T�C�Y
int Image::ModelHandle{ -1 };
int Image::sphere{ -1 };
int Image::Boss{ -1 };

void Image::Init()
{
	//�����Ń��[�h
	Image::LoadDivGraphs("ResourceFile/ImageFile/mapchip.png", mapChip); // ���������m�ی�div�摜�����[�h
	for (int i = 0; i < mapChip.AllNum; i++)
	{   // �摜�Ǎ����s
		if (mapChip.HandleArray[i] == -1) assert("�}�b�v�`�b�v" + std::to_string(i) + "�ԓǍ����s" == "");
	}

	Image::LoadDivGraphs("ResourceFile/ImageFile/magic2.png", Explo); // ���������m�ی�div�摜�����[�h
	for (int i = 0; i < Explo.AllNum; i++)
	{   // �摜�Ǎ����s
		if (Explo.HandleArray[i] == -1) assert("explo" + std::to_string(i) + "�ԓǍ����s" == "");
	}


	ModelHandle = MV1LoadModel("ResourceFile/ImageFile/mutant.mv1");
	assert(ModelHandle != -1);

	sphere = MV1LoadModel("ResourceFile/ImageFile/sphere.mv1");
	assert(sphere != -1);

	Boss = LoadGraph("ResourceFile/ImageFile/boss1.png");
	assert(Boss != -1);


	//suisui = LoadGraph("ResourceFile/ImageFile/suisui.gif");
	//assert(suisui != -1);
}


int Image::LoadDivGraphs(const TCHAR* FileName, DivImage& divImage)
{
	return DxLib::LoadDivGraph(FileName, divImage.XNum * divImage.YNum, divImage.XNum, divImage.YNum, divImage.XSize, divImage.YSize, divImage.HandleArray);
}

