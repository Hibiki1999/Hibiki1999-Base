#ifndef CSV_STRUCT_H_
#define CSV_STRUCT_H_

#include "../NotChangingLibrary/StringDataCsv.h"
#include "../NotChangingLibrary/DataCSV.h"

struct  CsvString :public StringDataCSV
{
	std::string noneData = "";
	CsvString(std::string filePath = "") :StringDataCSV(filePath)
	{

	}
	~CsvString() { clear(); };

	void Load(std::string filePath)
	{
		assert(filePath != "" && "�t�@�C����filepath��ݒ肵�Ă�������" != "");
		StringDataCSV::Load(filePath);
	}
};

struct CsvInt :public DataCSV
{
	int NoneData = -1;
	int CellSize = 1;
	CsvInt(int CellSize = 1, std::string filepath = "") :DataCSV(filepath)
	{
		assert(CellSize > 0 && "�}�X�ڃT�C�Y�w��CellSize��1�ȏ�ɐݒ肵�Ă��������I" != "");
		this->CellSize = CellSize;
	}
	~CsvInt() { clear(); };

	void Load(int CellSize, std::string filepath)
	{
		assert(filepath != "" && "�t�@�C����filepath��ݒ肵�Ă�������" != "");
		DataCSV::Load(filepath);
	}
};

#endif // !CSV_STRUCT_H_
