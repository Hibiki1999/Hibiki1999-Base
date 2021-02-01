#include "Image.h"
#include <string>

DivImage Image::mapChip{ 16, 16, 32, 32 };//Xの数、Yの数、Xのサイズ、Yのサイズ


void Image::Init()
{
	//ここでロード
	Image::LoadDivGraphs("Resource/Image/ImageFile/mapchip.png", mapChip); // メモリを確保後div画像をロード
	for (int i = 0; i < mapChip.AllNum; i++)
	{   // 画像読込失敗
		if (mapChip.HandleArray[i] == -1) assert("マップチップ" + std::to_string(i) + "番読込失敗" == "");
	}
}

int Image::LoadDivGraphs(const TCHAR* FileName, DivImage& divImage)
{
	return DxLib::LoadDivGraph(FileName, divImage.XNum * divImage.YNum, divImage.XNum, divImage.YNum, divImage.XSize, divImage.YSize, divImage.HandleArray);
}

