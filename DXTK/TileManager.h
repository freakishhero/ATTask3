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
	TileManager(GameData* _GD, ID3D11Device* _d3d_device);
	~TileManager();

	Tile* createTile(int ID, TileType _type, DirectX::SimpleMath::Vector2 _position);
	void CheckSurfaceTile(Tile* _tile, GameData* _GD);
	wchar_t* charToWChar(const char* _string);
	void Tick(GameData* _GD);

private:
	std::vector<Sprite*> tileSprites;
	float elapsed = 0;
};