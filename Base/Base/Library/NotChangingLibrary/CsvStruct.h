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
		assert(filePath != "" && "ファイル名filepathを設定してください" != "");
		StringDataCSV::Load(filePath);
	}
};

struct CsvInt :public DataCSV
{
	int NoneData = -1;
	int CellSize = 1;
	CsvInt(int CellSize = 1, std::string filepath = "") :DataCSV(filepath)
	{
		assert(CellSize > 0 && "マス目サイズ指定CellSizeは1以上に設定してください！" != "");
		this->CellSize = CellSize;
	}
	~CsvInt() { clear(); };

	void Load(int CellSize, std::string filepath)
	{
		assert(filepath != "" && "ファイル名filepathを設定してください" != "");
		DataCSV::Load(filepath);
	}
};

#endif // !CSV_STRUCT_H_
