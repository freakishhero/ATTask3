#include "Sprite.h"
#include "StringUtils.h"

#include <DDSTextureLoader.h>

Sprite::Sprite(const std::string& _file_name, ID3D11Device* _d3d_device)
{
	std::string fullfilename = "" + _file_name + ".dds";

	HRESULT hr = DirectX::CreateDDSTextureFromFile(_d3d_device, StringUtils::charToWChar(fullfilename.c_str()), nullptr, &sprite_rv);

	// Find size of image.
	ID3D11Resource *pResource;
	sprite_rv->GetResource(&pResource);
	static_cast<ID3D11Texture2D*>(pResource)->GetDesc(&desc);
}


/* Cleans up dynamically allocated memory.
*/
Sprite::~Sprite()
{
	if (sprite_rv)
	{
		sprite_rv->Release();
		sprite_rv = nullptr;
	}
}


/* Returns resource view information for drawing the texture.
*/
ID3D11ShaderResourceView* Sprite::getResourceView() const
{
	return sprite_rv;
}


int Sprite::getWidth() const
{
	return desc.Width;
}


int Sprite::getHeight() const
{
	return desc.Height;
}
