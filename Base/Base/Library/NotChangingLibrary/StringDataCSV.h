#ifndef STRING_DATA_CSV_H_
#define STRING_DATA_CSV_H_

#include<memory>
#include<vector>
#include <string>
#include<fstream>
#include<string>
#include<sstream>
#include<assert.h>

struct StringDataCSV
{
	std::string FilePath = "";
	int Width = 0;
	int Height = 0;
	std::vector<std::vector<std::string>> Data;

	std::vector<std::string>& operator[](std::size_t index) {
		return Data[index];//書き込み
	}

	std::vector<std::string> operator[](std::size_t index) const {
		return Data[index];//読み取り
	}

	std::size_t size()
	{
		return Data.size();
	}

	StringDataCSV(std::string FilePath = "") :FilePath{ FilePath }
	{
		if (FilePath != "")Load(FilePath);
	}

	virtual ~StringDataCSV()
	{
		Data.clear();
	}

	virtual void clear()
	{
		Data.clear();
	}

	void Load(std::string filePath)
	{
		if (filePath == "")return;//パスがなければスキップ
		FilePath = filePath;
		Data.clear();//先にメモリー開け
		std::ifstream ifs_csv_file(filePath);//Csvファイルを読み込み
		std::string line;//文字列メモリー保存

		int readWidth = 0;
		int maxWidth = 0;
		int readHeight = 0;//csvファイルの高さと広さを検索と保存用
		while (std::getline(ifs_csv_file, line))//一行ずつ読み込む
		{
			std::vector<std::string> dataList;//他のリストを用意
			std::istringstream linestream(line);//linestreamにlineを入れる(getlineに対応するため、line(string)をlinestreamに変更)
			std::string splitted;//区切りした文字を一時保存場所を設置
			int widthCount = 0;//csvの広さを検索
			while (std::getline(linestream, splitted, { ',' }))//linestreamをカンマで区切りしてsplittedに入れる
			{
				dataList.push_back(splitted);//区切りした文字をdataListに保存
				widthCount++;//広さを検索
			}
			if (widthCount > maxWidth)maxWidth = widthCount;//検索した広さを最大に設定する

			if (dataList.size() != 0)Data.push_back(dataList);//dataListに保存したデータを二次元配列に入れる
			readHeight++;//次の行に行く前に高さを検索
		}
		readWidth = maxWidth;//検索した高さを最大に設定する

		assert(readWidth > 0);
		assert(readHeight > 0);//広さか高さが0になったらエラー

		Width = readWidth;
		Height = readHeight;//高さと広さを他の場所でも読めるために事前で用意した処に入れる

	}
};

#endif // !STRING_DATA_CSV_H_
