#include "Sprite.h"
#include <DDSTextureLoader.h>

Sprite::Sprite(const wchar_t* _file_name, ID3D11Device* _d3d_device)
{
	HRESULT hr = DirectX::CreateDDSTextureFromFile(_d3d_device, _file_name, nullptr, &sprite_resource_view);

	// Find size of image.
	ID3D11Resource *pResource;
	sprite_resource_view->GetResource(&pResource);
	static_cast<ID3D11Texture2D*>(pResource)->GetDesc(&description);
}


/* Cleans up dynamically allocated memory.
*/
Sprite::~Sprite()
{
	if (sprite_resource_view)
	{
		sprite_resource_view->Release();
		sprite_resource_view = nullptr;
	}
}


/* Returns resource view information for drawing the texture.
*/
ID3D11ShaderResourceView* Sprite::getResourceView() const
{
	return sprite_resource_view;
}


int Sprite::getWidth() const
{
	return description.Width;
}


int Sprite::getHeight() const
{
	return description.Height;
}
