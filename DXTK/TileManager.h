#pragma once
#include <d3d11.h>
#include "SimpleMath.h"
#include <vector>

enum class TileType;
class Tile;
class Sprite;

class TileManager
{
public:
	TileManager(ID3D11Device* _d3d_device);
	~TileManager();

	Tile* createTile(TileType _type, DirectX::SimpleMath::Vector2 _position);

private:
	std::vector<Sprite*> tileSprites;
};