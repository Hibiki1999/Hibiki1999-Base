#ifndef DATASAVE_H_
#define DATASAVE_H_

#include "../NotChangingLibrary/json.hpp"
#include "../GameManager/GameManager.h"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

class DataSave
{

public:
	DataSave() {};
	~DataSave() {};

	void Save();

	void Load();

private:
	GameManager& gm = GameManager::GetInstance();
};

#endif // !DATASAVE_H_
