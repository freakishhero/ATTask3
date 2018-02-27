#include "LevelLoader.h"

LevelLoader::LevelLoader()
{
	
}

LevelLoader::~LevelLoader()
{
}

void LevelLoader::LoadLevel(std::string _file_name)
{
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
	}
	else 
	{
		std::cout << "File not found" << std::endl;
	}

	std::cout << "Tile Types:" << std::endl;
	for (int i = 0; i < tile_types.size(); i++) 
	{
		std::cout << tile_types[i] << std::endl;
	}
}
