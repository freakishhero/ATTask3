#pragma once
#include "SpriteBatch.h"
#include "SpriteFont.h"

//=================================================================
//Data to be passed by game to all 2D Game Objects via Draw 
//=================================================================

struct DrawData2D
{
	std::unique_ptr<DirectX::SpriteBatch> sprite_batch;
	std::unique_ptr<DirectX::SpriteFont> font;
};
