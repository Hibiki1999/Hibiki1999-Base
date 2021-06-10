#include "DataSave.h"
#include "../../Scene/Child/Title/Title.h"

void DataSave::Save()
{
    json j;
    //ここからセーブしたいデータを追加
   // j["titleTest"] = Title::test;


    //ここまで============================
     std::ofstream outputFile("SaveData/DATA.json");
     outputFile << j;
}

void DataSave::Load()
{
    std::ifstream loadFile("SaveData/DATA.json");
    json jl = json::parse(loadFile);
    //ここからロードしたいデータを追加
    //Title::test = jl["titleTest"];
}