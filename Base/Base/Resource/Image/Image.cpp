#include "Image.h"
#include <string>

DivImage Image::mapChip{ 16, 16, 32, 32 };//Xの数、Yの数、Xのサイズ、Yのサイズ
int Image::ModelHandle{ -1 };
int Image::sword{ -1 };

void Image::Init()
{
	//ここでロード
	Image::LoadDivGraphs("ResourceFile/ImageFile/mapchip.png", mapChip); // メモリを確保後div画像をロード
	for (int i = 0; i < mapChip.AllNum; i++)
	{   // 画像読込失敗
		if (mapChip.HandleArray[i] == -1) assert("マップチップ" + std::to_string(i) + "番読込失敗" == "");
	}


	ModelHandle = MV1LoadModel("ResourceFile/ImageFile/mutant.mv1");
	assert(ModelHandle != -1);

	//sword = MV1LoadModel("ResourceFile/ImageFile/maria_prop_j_j_ong.mv1");
	//assert(sword != -1);


	//suisui = LoadGraph("ResourceFile/ImageFile/suisui.gif");
	//assert(suisui != -1);
}


int Image::LoadDivGraphs(const TCHAR* FileName, DivImage& divImage)
{
	return DxLib::LoadDivGraph(FileName, divImage.XNum * divImage.YNum, divImage.XNum, divImage.YNum, divImage.XSize, divImage.YSize, divImage.HandleArray);
}

