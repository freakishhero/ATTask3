#pragma once
#include "GameObject2D.h"

class Sprite;
class BoundingBox2D;

class SpriteGameObject : public GameObject2D
{
public:
	SpriteGameObject(Sprite* _texture = nullptr, RECT* _rect = nullptr);
	virtual ~SpriteGameObject();

	virtual void Tick(GameData* _GD) override;
	virtual void Draw(DrawData2D* _DD) override;

	Sprite* SpriteGameObject::LoadSprite(const std::string& file_name);
	Sprite* GetSprite() const;
	void SetSprite(Sprite* _sprite);
	void CenterOrigin();

	virtual bool IsVisible() const;
	virtual void SetVisible(bool _visible);

	RECT* GetRect() const;
	void SetRect(RECT* _rect);


protected:
	Sprite* sprite;
	bool visible;
	RECT* rect;

};
