#ifndef  DATACSV_H_
#define  DATACSV_H_

#include<memory>
#include<vector>
#include <string>
#include<fstream>
#include<string>
#include<sstream>
#include<assert.h>

struct DataCSV
{
	std::string FilePath = "";
	int Width = 0;
	int Height = 0;
	std::vector<std::vector<int>>Data;

	std::vector<int>& operator[](std::size_t index) {
		return Data[index];//èëÇ´çûÇ›
	}

	std::vector<int> operator[](std::size_t index) const {
		return Data[index];//ì«Ç›éÊÇË
	}



	std::size_t size()
	{
		return Data.size();
	}

	DataCSV(std::string FilePath = "") :FilePath{ FilePath }
	{
		if (FilePath != "")Load(FilePath);
	}

	virtual ~DataCSV()
	{
		Data.clear();
	}

	virtual void clear()
	{
		Data.clear();
	}

	void Load(std::string filepath)
	{
		if (filepath == "")return;
		FilePath = filepath;
		Data.clear();
		std::ifstream ifs_csv_file(filepath);
		std::string line;

		int readWidth = 0;
		int maxWidth = 0;
		int readHeight = 0;
		while (std::getline(ifs_csv_file, line))
		{
			std::vector<int>numlist;
			std::istringstream linestream(line);
			std::string splitted;
			int widthCount = 0;
			while (std::getline(linestream, splitted, { ',' }))
			{
				std::istringstream ss;
				ss = std::istringstream(splitted);
				int num;
				ss >> num;
				numlist.push_back(num);
				widthCount++;
			}
			if (widthCount > maxWidth)maxWidth = widthCount;

			if (numlist.size() != 0)Data.push_back(numlist);
			readHeight++;
		}
		readWidth = maxWidth;
		
		assert(readWidth > 0);
		assert(readHeight > 0);

		this->Width = readWidth;
		this->Height = readHeight;

		return;
	}
};
#endif // ! DATACSV_H_
