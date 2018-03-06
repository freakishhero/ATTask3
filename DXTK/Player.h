#pragma once
#include "SpriteGameObject.h"

enum PlayerState;
enum class TileType;
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
	void SetTileEditor(TileEditor*);
	void SetMoveLeft(bool _state);
	void SetMoveRight(bool _state);
	void SetMoveDown(bool _state);
	TileEditor* GetTileEditor();
	void EnableEditMode();
	void DisableEditMode();

private:
	PlayerState player_state;
	TileEditor* tile_editor;
	bool can_move_left;
	bool can_move_right;
	bool can_move_down;
};
