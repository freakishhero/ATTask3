#pragma once
#include <d3d11.h>
#include "SimpleMath.h"
#include <vector>

enum class TileType;
class Tile;
class GameData;
class Sprite;

class TileManager
{
public:
	TileManager(ID3D11Device* _d3d_device);
	~TileManager();

	Tile* createTile(int ID, TileType _type, DirectX::SimpleMath::Vector2 _position);
	void CheckSurfaceTile(Tile* _tile, GameData* _GD);
	void Tick(GameData* _GD);

private:
	std::vector<Sprite*> tileSprites;
};