#include "Sound.h"
#include <string>

//int Sound::explo{ -1 };
//int Sound::shut{ -1 };
//int Sound::hit{ -1 };
//std::string Sound::bgm1{ "ResourceFile/SoundFile/BGM/1.mp3" };


#ifdef _DEBUG

std::vector<std::string> Sound::checkPath{ "0" };
int Sound::check{ -1 };

void Sound::Init()
{
	checkPath.clear();//リストを綺麗にする
	LoadToList();//指定したパスをリストに入れる
	for (int i = 0; i < checkPath.size(); i++)
	{
		check = LoadSoundMem(checkPath[i].c_str());//メモリにロードしてみる
		assert(check != -1);//ロード失敗したらエラーが出る
		DeleteSoundMem(check);//ロードした音源を削除
		check = -1;//次のロードを準備
	}
	checkPath.clear();//リストのメモリを減らす
}

void Sound::LoadToList()
{
	//ここに確認したいパスを入れる
	//checkPath.push_back(bgm1);
}

#endif // _DEBUG

