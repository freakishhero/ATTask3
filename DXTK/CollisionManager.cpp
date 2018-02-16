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

	player->GetPhysics()->enableGravity(true);
	player->SetMoveLeft(true);
	player->SetMoveRight(true);
	player->SetMoveDown(true);

	if (_GD->player_state != PlayerState::PS_JUMPING)
	{
		_GD->player_state = PlayerState::PS_GROUNDED;
	}

	for (auto& tile : _GD->tiles)
	{
		if (tile->GetTileType() != TileType::AIR)
		{
			if (topCollision(player->GetCollisions(), tile->GetCollisions()))
			{
				std::cout << "top collision" << std::endl;
				player->ModifyPos(Vector2(0, 0.1));
			}

			if (bottomCollision(player->GetCollisions(), tile->GetCollisions()))
			{
				std::cout << "bottom collision" << std::endl;
				player->SetMoveDown(false);
				player->GetPhysics()->setVelocity(Vector2::Zero);
				player->GetPhysics()->setAcceleration(Vector2::Zero);
			}

			if (leftCollision(player->GetCollisions(), tile->GetCollisions()))
			{
				std::cout << "left collision" << std::endl;
				player->SetMoveLeft(false);
			}

			if (rightCollision(player->GetCollisions(), tile->GetCollisions()))
			{
				std::cout << "right collision" << std::endl;
				player->SetMoveRight(false);
			}
		}
	}
}

void CollisionManager::initPlayer(Player* _player)
{
	player = _player;
}

bool CollisionManager::leftCollision(CollisionComponent* _player_box, CollisionComponent* _object_box)
{
	if (_player_box->GetLeft() < _object_box->GetRight()
		&& _player_box->GetLeft() > _object_box->GetLeft())
	{
		if (_player_box->GetTop() > _object_box->GetTop() - 64
			&& _player_box->GetTop() < (_object_box->GetBottom()))
			return true;
	}
	return false;
}

bool CollisionManager::rightCollision(CollisionComponent* _player_box, CollisionComponent* _object_box)
{
	if (_player_box->GetRight() > _object_box->GetLeft() &&
		_player_box->GetRight() < _object_box->GetRight())
	{
		if (_player_box->GetTop() > _object_box->GetTop() - 64
			&& _player_box->GetTop() < (_object_box->GetBottom()))
			return true;
	}
	return false;
}

bool CollisionManager::topCollision(CollisionComponent* _player_box, CollisionComponent* _object_box)
{
	if (_player_box->GetTop() <= _object_box->GetBottom()
		&& _player_box->GetTop() >= _object_box->GetTop() + 32)
	{
		if (_player_box->GetLeft() >= _object_box->GetLeft() - 64
			&& _player_box->GetRight() <= (_object_box->GetRight() + 64))
			return true;
	}
	return false;
}

bool CollisionManager::bottomCollision(CollisionComponent* _player_box, CollisionComponent* _object_box)
{
	if (_player_box->GetBottom() >= _object_box->GetTop()
		&& _player_box->GetBottom() <= _object_box->GetBottom())
	{
		if (_player_box->GetLeft() <= (_object_box->GetRight())
			&& _player_box->GetLeft() >= _object_box->GetLeft() - 64)
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