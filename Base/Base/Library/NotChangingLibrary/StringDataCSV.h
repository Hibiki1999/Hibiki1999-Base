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
		return Data[index];//��������
	}

	std::vector<std::string> operator[](std::size_t index) const {
		return Data[index];//�ǂݎ��
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
		if (filePath == "")return;//�p�X���Ȃ���΃X�L�b�v
		FilePath = filePath;
		Data.clear();//��Ƀ������[�J��
		std::ifstream ifs_csv_file(filePath);//Csv�t�@�C����ǂݍ���
		std::string line;//�����񃁃����[�ۑ�

		int readWidth = 0;
		int maxWidth = 0;
		int readHeight = 0;//csv�t�@�C���̍����ƍL���������ƕۑ��p
		while (std::getline(ifs_csv_file, line))//��s���ǂݍ���
		{
			std::vector<std::string> dataList;//���̃��X�g��p��
			std::istringstream linestream(line);//linestream��line������(getline�ɑΉ����邽�߁Aline(string)��linestream�ɕύX)
			std::string splitted;//��؂肵���������ꎞ�ۑ��ꏊ��ݒu
			int widthCount = 0;//csv�̍L��������
			while (std::getline(linestream, splitted, { ',' }))//linestream���J���}�ŋ�؂肵��splitted�ɓ����
			{
				dataList.push_back(splitted);//��؂肵��������dataList�ɕۑ�
				widthCount++;//�L��������
			}
			if (widthCount > maxWidth)maxWidth = widthCount;//���������L�����ő�ɐݒ肷��

			if (dataList.size() != 0)Data.push_back(dataList);//dataList�ɕۑ������f�[�^��񎟌��z��ɓ����
			readHeight++;//���̍s�ɍs���O�ɍ���������
		}
		readWidth = maxWidth;//���������������ő�ɐݒ肷��

		assert(readWidth > 0);
		assert(readHeight > 0);//�L����������0�ɂȂ�����G���[

		Width = readWidth;
		Height = readHeight;//�����ƍL���𑼂̏ꏊ�ł��ǂ߂邽�߂Ɏ��O�ŗp�ӂ������ɓ����

	}
};

#endif // !STRING_DATA_CSV_H_
