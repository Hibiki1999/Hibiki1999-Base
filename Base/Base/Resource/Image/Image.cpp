#include "Image.h"
#include <string>

DivImage Image::mapChip{ 16, 16, 32, 32 };//X�̐��AY�̐��AX�̃T�C�Y�AY�̃T�C�Y


void Image::Init()
{
	//�����Ń��[�h
	Image::LoadDivGraphs("Resource/Image/ImageFile/mapchip.png", mapChip); // ���������m�ی�div�摜�����[�h
	for (int i = 0; i < mapChip.AllNum; i++)
	{   // �摜�Ǎ����s
		if (mapChip.HandleArray[i] == -1) assert("�}�b�v�`�b�v" + std::to_string(i) + "�ԓǍ����s" == "");
	}
}

int Image::LoadDivGraphs(const TCHAR* FileName, DivImage& divImage)
{
	return DxLib::LoadDivGraph(FileName, divImage.XNum * divImage.YNum, divImage.XNum, divImage.YNum, divImage.XSize, divImage.YSize, divImage.HandleArray);
}

