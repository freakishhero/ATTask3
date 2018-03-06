#include "LevelLoader.h"

LevelLoader::LevelLoader()
{
	
}

LevelLoader::~LevelLoader()
{
}

std::vector<int> LevelLoader::LoadLevel(std::string _file_name)
{
	std::fstream level_file;
	std::vector<int> tile_types;

	level_file.open("../Assets/Levels/"  + _file_name + ".txt", std::ios::in | std::ios::binary);
	int tile_type = 0;

	if (level_file.is_open()) 
	{
		while (level_file >> tile_type)
		{
			tile_types.push_back(tile_type);
			level_file.get();
		}
		std::cout << "File successfully loaded" << std::endl;
		level_file.close();
	}
	else 
	{
		std::cout << "File not found" << std::endl;
	}

	return tile_types;
}

void LevelLoader::SaveLevel(std::vector<int> tile_types)
{
	std::ofstream level_file("../Assets/Levels/level_02.txt");

	for (auto& type : tile_types)
	{
		level_file << type << ",";
	}
	level_file << std::endl;

	level_file.close();
}
