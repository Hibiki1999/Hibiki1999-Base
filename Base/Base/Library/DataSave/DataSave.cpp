#include "DataSave.h"
#include "../../Scene/Child/Title/Title.h"

void DataSave::Save()
{
    json j;
    //��������Z�[�u�������f�[�^��ǉ�
   // j["titleTest"] = Title::test;


    //�����܂�============================
     std::ofstream outputFile("SaveData/DATA.json");
     outputFile << j;
}

void DataSave::Load()
{
    std::ifstream loadFile("SaveData/DATA.json");
    json jl = json::parse(loadFile);
    //�������烍�[�h�������f�[�^��ǉ�
    //Title::test = jl["titleTest"];
}