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
				player->GetPhysics()->setVelocity(Vector2(0, 1.0));
			}
			else
			{
				if (bottomCollision(player->GetCollisions(), tile->GetCollisions()))
				{
					if (_GD->player_state == PlayerState::PS_JUMPING)
					{
						player->GetPhysics()->setAcceleration(Vector2::Zero);
					}

					std::cout << "bottom collision" << std::endl;
					player->GetPhysics()->enableGravity(false);
					player->GetPhysics()->setVelocity(Vector2::Zero);
					_GD->player_state = PlayerState::PS_GROUNDED;
					//player->ModifyPos(Vector2(0, -20.0f) * _GD->delta_time);
					player->SetPos(Vector2(player->GetPos().x, tile->GetPos().y - 64));
				}

				if (leftCollision(player->GetCollisions(), tile->GetCollisions()))
				{
					std::cout << "left collision" << std::endl;
					//player->ModifyPos(Vector2(10.0f, -0.1f) * _GD->delta_time);
					player->SetPos(Vector2(tile->GetPos().x + 64, player->GetPos().y));
					player->SetMoveLeft(false);
				}

				if (rightCollision(player->GetCollisions(), tile->GetCollisions()))
				{
					std::cout << "right collision" << std::endl;
					//player->ModifyPos(Vector2(-10.0f, -0.1f) * _GD->delta_time);
					player->SetPos(Vector2(tile->GetPos().x - 64, player->GetPos().y));
					player->SetMoveRight(false);
				}
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
	if (_player_box->GetLeft() <= _object_box->GetRight()
		&& _player_box->GetLeft() >= _object_box->GetLeft())
	{
		if (_player_box->GetTop() >= _object_box->GetTop()
			&& _player_box->GetTop() <= (_object_box->GetBottom() - 1))
			return true;
	}
	return false;
}


bool CollisionManager::rightCollision(CollisionComponent* _player_box, CollisionComponent* _object_box)
{
	if (_player_box->GetRight() >= _object_box->GetLeft() &&
		_player_box->GetRight() <= _object_box->GetRight())
	{
		if (_player_box->GetTop() >= _object_box->GetTop()
			&& _player_box->GetTop() <= (_object_box->GetBottom() - 1))
			return true;
	}

	return false;
}


bool CollisionManager::topCollision(CollisionComponent* _player_box, CollisionComponent* _object_box)
{
	if (_player_box->GetTop() <= _object_box->GetBottom()
		&& _player_box->GetTop() >= _object_box->GetTop())
	{
		if (_player_box->GetLeft() >= _object_box->GetLeft() - (64 / 2)
			&& _player_box->GetRight() <= (_object_box->GetRight()) + (64 / 2))
			return true;
	}
	return false;
}


bool CollisionManager::bottomCollision(CollisionComponent* _player_box, CollisionComponent* _object_box)
{
	if (_player_box->GetBottom() >= _object_box->GetTop()
		&& _player_box->GetBottom() <= _object_box->GetBottom())
	{
		if (_player_box->GetLeft() <= (_object_box->GetRight()) - 64 / 8
			&& _player_box->GetLeft() - 8 >= _object_box->GetLeft() - 64)
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