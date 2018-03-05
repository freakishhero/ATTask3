#pragma once
#include <fstream>
#include <iostream>
#include <vector>
class LevelLoader
{
public:
	LevelLoader();
	~LevelLoader();

	std::vector<int> LoadLevel(std::string _file_name);
	void SaveLevel(std::vector<int> tile_types);

private:
};