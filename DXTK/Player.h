#pragma once
#include "SpriteGameObject.h"

class Player : public SpriteGameObject
{
public:
	Player(Sprite* _sprite);
	virtual ~Player();

	virtual void Tick(GameData* _GD) override;
	virtual void Draw(DrawData2D* _DD) override;

	bool IsVisible() const override;
	void SetVisible(bool _visible) override;

private:
	float move_speed;
	float jump_height;
	bool visible;
};
