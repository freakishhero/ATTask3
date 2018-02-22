#pragma once
#include <vector>
#include <memory>

class Tile;
class PerlinNoise;
struct GameData;
struct DrawData2D;

class Chunk
{
public:
	Chunk(GameData* _GD);
	~Chunk();

	void Tick(GameData* _GD);
	void Draw(DrawData2D* _DD);
	std::vector<Tile*> GetTiles() const;

private:
	int ID = 0;
	std::vector<Tile*> tiles;
	std::unique_ptr<PerlinNoise> noise;
};