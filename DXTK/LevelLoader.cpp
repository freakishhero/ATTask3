#include "LevelLoader.h"

LevelLoader::LevelLoader()
{
	
}

LevelLoader::~LevelLoader()
{
}

void LevelLoader::LoadLevel(std::string _file_name)
{
	level_file.open("level_1.txt", std::ios::in | std::ios::binary);

	/*if (level_file.is_open()) {
		while (level_file >> number) {
			numbers.push_back(number);
			level_file.get();
		}
	}

	cout << "Numbers:\n";
	for (int i = 0; i < numbers.size(); i++) {
		cout << numbers[i] << '\n';
	}*/
}
