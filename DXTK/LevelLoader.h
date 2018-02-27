#pragma once
#include <fstream>
#include <iostream>
#include <vector>
class LevelLoader
{
public:
	LevelLoader();
	~LevelLoader();

	void LoadLevel(std::string _file_name);

private:
	std::fstream level_file;
	std::vector<int> tile_types;
};