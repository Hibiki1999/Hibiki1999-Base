#include "Image.h"
#include <string>

DivImage Image::mapChip{ 16, 16, 32, 32 };//X�̐��AY�̐��AX�̃T�C�Y�AY�̃T�C�Y
int Image::suisui{ -1 };

void Image::Init()
{
	//�����Ń��[�h
	Image::LoadDivGraphs("ResourceFile/ImageFile/mapchip.png", mapChip); // ���������m�ی�div�摜�����[�h
	for (int i = 0; i < mapChip.AllNum; i++)
	{   // �摜�Ǎ����s
		if (mapChip.HandleArray[i] == -1) assert("�}�b�v�`�b�v" + std::to_string(i) + "�ԓǍ����s" == "");
	}

	suisui = LoadGraph("ResourceFile/ImageFile/suisui.gif");
	assert(suisui != -1);
}

int Image::LoadDivGraphs(const TCHAR* FileName, DivImage& divImage)
{
	return DxLib::LoadDivGraph(FileName, divImage.XNum * divImage.YNum, divImage.XNum, divImage.YNum, divImage.XSize, divImage.YSize, divImage.HandleArray);
}

