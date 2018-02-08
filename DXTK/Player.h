#pragma once
#include "SpriteGameObject.h"

enum PlayerState;
class TileEditor;

class Player : public SpriteGameObject
{
public:
	Player(Sprite* _sprite);
	virtual ~Player();

	virtual void Tick(GameData* _GD) override;
	virtual void Draw(DrawData2D* _DD) override;

	bool IsVisible() const override;
	void SetVisible(bool _visible) override;
	void SetEditMode(bool _state);

private:
	PlayerState player_state;
	TileEditor* tile_editor;
	float move_speed;
	float jump_height;
	bool visible;
	bool edit_mode = false;
};
