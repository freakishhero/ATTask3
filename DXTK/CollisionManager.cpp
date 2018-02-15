#include "CollisionManager.h"
#include "Player.h"
#include "GameData.h"
#include "Tile.h"
#include "GameObject2D.h"
#include "PhysicsComponent.h"
#include "CollisionComponent.h"
#include "PlayerStates.h"

#include <iostream>

CollisionManager::CollisionManager()
	: player(nullptr)
{
}

void CollisionManager::tick(GameData* _GD)
{
	// Only continue if the player and level is initialised.
	if (!player)
		return;

	for (auto& tile : _GD->tiles)
	{
		if (topCollision(player->getCollisions(), tile->getCollisions()))
		{
				std::cout << "top collision" << std::endl;
				player->getPhysics()->setVelocity(Vector2(0, 3.0));
		}

		if (bottomCollision(player->getCollisions(), tile->getCollisions()))
		{
				std::cout << "bottom collision" << std::endl;
				player->getPhysics()->enableGravity(false);
				player->getPhysics()->setVelocity(Vector2::Zero);
				_GD->player_state = PlayerState::PS_GROUNDED;
				player->ModifyPos(Vector2(0, -0.1f));
		}

		if (leftCollision(player->getCollisions(), tile->getCollisions()))
		{
				std::cout << "left collision" << std::endl;
				player->ModifyPos(Vector2(0.1f, 0.0f));
		}

		if (rightCollision(player->getCollisions(), tile->getCollisions()))
		{
				std::cout << "right collision" << std::endl;
				player->ModifyPos(Vector2(-0.1f, 0.0f));
		}
	}
}


void CollisionManager::initPlayer(Player* _player)
{
	player = _player;
}



bool CollisionManager::leftCollision(CollisionComponent* _player_box, CollisionComponent* _object_box)
{
	if (_player_box->getLeft() < _object_box->getRight() + 64
		&& _player_box->getLeft() > _object_box->getLeft())
	{
		if (_player_box->getTop() > _object_box->getTop() - (64 * 0.95)
			&& _player_box->getTop() < _object_box->getBottom() + 64)
			return true;
	}
	return false;
}


bool CollisionManager::rightCollision(CollisionComponent* _player_box, CollisionComponent* _object_box)
{
	if (_player_box->getRight() + 64 > _object_box->getLeft() &&
		_player_box->getRight() + 64 < _object_box->getRight() + 64)
	{
		if (_player_box->getTop() > _object_box->getTop() - (64 * 0.95)
			&& _player_box->getTop() < _object_box->getBottom() + 64)
			return true;
	}
	return false;
}


bool CollisionManager::topCollision(CollisionComponent* _player_box, CollisionComponent* _object_box)
{
	if (_player_box->getTop() < _object_box->getBottom() + 64
		&& _player_box->getTop() > _object_box->getTop())
	{
		if (_player_box->getLeft() > _object_box->getLeft() - (64 / 2)
			&& _player_box->getRight() + 64 < (_object_box->getRight() + 64) + (64 / 2))
			return true;
	}
	return false;
}


bool CollisionManager::bottomCollision(CollisionComponent* _player_box, CollisionComponent* _object_box)
{
	if (_player_box->getBottom() + 64 > _object_box->getTop()
		&& _player_box->getBottom() + 64 < _object_box->getBottom() + 64)
	{
		if (_player_box->getLeft() < (_object_box->getRight() + 64) - 64 / 8
			&& _player_box->getLeft() > _object_box->getLeft() - 64 / 2)
			return true;
	}
	return false;
}


bool CollisionManager::checkCollision(CollisionComponent * _box_1, CollisionComponent * _box_2)
{
	if (topCollision(_box_1, _box_2) ||
		bottomCollision(_box_1, _box_2) ||
		leftCollision(_box_1, _box_2) ||
		rightCollision(_box_1, _box_2))
	{
		return true;
	}

	return false;
}