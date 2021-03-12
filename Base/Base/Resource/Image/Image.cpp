#include "Image.h"
#include <string>

DivImage Image::mapChip{ 16, 16, 32, 32 };//X�̐��AY�̐��AX�̃T�C�Y�AY�̃T�C�Y
std::vector<int> Image::listImage{ 0 };
std::vector<std::vector<int>> Image::tDiDIv{ 0 };
std::vector<int> Image::sTDiDiv{ 0 };

void Image::Init()
{
	//�����Ń��[�h
	Image::LoadDivGraphs("ResourceFile/ImageFile/mapchip.png", mapChip); // ���������m�ی�div�摜�����[�h
	for (int i = 0; i < mapChip.AllNum; i++)
	{   // �摜�Ǎ����s
		if (mapChip.HandleArray[i] == -1) assert("�}�b�v�`�b�v" + std::to_string(i) + "�ԓǍ����s" == "");
	}

	//suisui = LoadGraph("ResourceFile/ImageFile/suisui.gif");
	//assert(suisui != -1);
}

void Image::SaveToVector(int image)
{
	listImage.push_back(image);
}

void Image::SaveTotDiDiv(DivImage& traget)
{
	for (int i = 0; i < traget.AllNum; i++)
	{
		sTDiDiv.push_back(traget.HandleArray[i]);
	}
	tDiDIv.push_back(sTDiDiv);
	sTDiDiv.clear();
}

int Image::LoadDivGraphs(const TCHAR* FileName, DivImage& divImage)
{
	return DxLib::LoadDivGraph(FileName, divImage.XNum * divImage.YNum, divImage.XNum, divImage.YNum, divImage.XSize, divImage.YSize, divImage.HandleArray);
}

