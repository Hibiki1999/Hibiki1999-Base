#include "Image.h"
#include <string>

DivImage Image::mapChip{ 16, 16, 32, 32 };//Xの数、Yの数、Xのサイズ、Yのサイズ
std::vector<int> Image::listImage{ 0 };
std::vector<std::vector<int>> Image::tDiDIv{ 0 };
std::vector<int> Image::sTDiDiv{ 0 };

void Image::Init()
{
	//ここでロード
	Image::LoadDivGraphs("ResourceFile/ImageFile/mapchip.png", mapChip); // メモリを確保後div画像をロード
	for (int i = 0; i < mapChip.AllNum; i++)
	{   // 画像読込失敗
		if (mapChip.HandleArray[i] == -1) assert("マップチップ" + std::to_string(i) + "番読込失敗" == "");
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

