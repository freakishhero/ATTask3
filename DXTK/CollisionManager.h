#pragma once
#include <vector>
#include "SpriteGameObject.h"

struct GameData;
class Player;
class Tile;

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager() = default;

	void tick(GameData* _GD);
	void initPlayer(Player* _player);

	bool leftCollision(CollisionComponent* _box_1, CollisionComponent* _box_2);
	bool rightCollision(CollisionComponent* _box_1, CollisionComponent* _box_2);
	bool topCollision(CollisionComponent* _box_1, CollisionComponent* _box_2);
	bool bottomCollision(CollisionComponent* _box_1, CollisionComponent* _box_2);
	bool checkCollision(CollisionComponent* _box_1, CollisionComponent* _box_2);

private:
	Player* player;

};