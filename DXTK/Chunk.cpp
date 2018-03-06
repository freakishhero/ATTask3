#include "Chunk.h"
#include "GameData.h"
#include "Tile.h"
#include "TileManager.h"
#include "TileType.h"
#include "PerlinNoise.h"

Chunk::Chunk(GameData* _GD)
{
	noise = std::make_unique<PerlinNoise>(rand() % 1000000 + 10000000);

	int id = 0;
	//Maybe store the min and max pos values for each chunk?
	for (int w = 0; w < 1920 / _GD->TILE_WIDTH; w++)
	{
		for (int h = 0; h < 1080 / _GD->TILE_HEIGHT; h++)
		{
			Vector2 pos = Vector2(w * _GD->TILE_WIDTH, h  * _GD->TILE_HEIGHT);
			tiles.push_back(_GD->tile_manager->createTile(id, TileType::AIR, Vector2(pos)));
			id++;
		}
	}

	for (int i = 0; i < 1920 / _GD->TILE_WIDTH; i++) //x = width 
	{
		int height = 2 + noise->generateNoise(i, _GD->TILE_HEIGHT / 6);

		for (int j = 1080 / _GD->TILE_HEIGHT; j > 1080 / _GD->TILE_HEIGHT - height; j--) //y = height
		{
			Vector2 pos = Vector2(i * _GD->TILE_WIDTH, j  * _GD->TILE_HEIGHT);
			for (auto& tile : tiles)
			{
				if (tile->GetPos() == pos)
				{
					int random = j == _GD->MAX_DEPTH - 1 ? rand() % 1 + 1 : rand() % 2 + 1;
					if (j == _GD->MAX_DEPTH)
					{
						//tiles.push_back(tile_manager->createTile(i, TileType::BEDROCK, Vector2(pos)));
						tile->SetTileType(TileType::BEDROCK);
					}
					else if (j > _GD->MAX_DEPTH - 4 && j < _GD->MAX_DEPTH && random == 1)
					{
						//tiles.push_back(tile_manager->createTile(game_data.tiles.size(), TileType::STONE, Vector2(pos)));
						tile->SetTileType(TileType::STONE);
					}
					else
					{
						//tiles.push_back(tile_manager->createTile(i, TileType::DIRT, Vector2(pos)));
						tile->SetTileType(TileType::DIRT);
					}
				}
			}
		}

		for (auto& tile : tiles)
		{
			if (!tile->IsSurfaceTile() && tile->GetTileType() != TileType::AIR)
			{
				if (tile->checkSurfaceTile(_GD))
				{
					tile->SetSurfaceTile(true);
				}
				else
				{
					tile->SetSurfaceTile(false);
				}
			}
		}
	}
}

Chunk::~Chunk()
{
}

void Chunk::Tick(GameData * _GD)
{
	for (auto& tile : tiles)
	{
		tile->Tick(_GD);
	}
}

void Chunk::Draw(DrawData2D * _DD)
{
	for (auto& tile : tiles)
	{
		tile->Draw(_DD);
	}
}

std::vector<Tile*> Chunk::GetTiles() const
{
	return tiles;
}

void Chunk::LoadChunkFromTile(std::vector<int> tile_types)
{
	for (auto& tile : tiles)
	{
		tile->SetTileType(TileType::AIR);
	}

	for (auto& tile : tiles)
	{
		for (int i = 0; i < tile_types.size(); i++)
		{
			if (tile_types[i] >= 0)
			{
				tile->SetTileType((TileType)tile_types[i]);
				tile_types[i] = -1;
				break;
			}
			else 
			{
				tile->SetTileType(TileType::AIR);
			}
		}
	}
}