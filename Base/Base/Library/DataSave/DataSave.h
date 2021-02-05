#ifndef DATASAVE_H_
#define DATASAVE_H_

#include "../NotChangingLibrary/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

class DataSave
{

public:
	DataSave() {};
	~DataSave() {};

	static void Save();

	static void Load();
};

#endif // !DATASAVE_H_
