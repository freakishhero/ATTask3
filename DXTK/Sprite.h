#pragma once
#include <d3d11_1.h>

#include <string>

class Sprite
{
public:
	Sprite(const std::string& _file_name, ID3D11Device* _d3d_device);
	~Sprite();

	ID3D11ShaderResourceView* getResourceView() const;
	int getWidth() const;
	int getHeight() const;

private:
	ID3D11ShaderResourceView* sprite_rv;
	D3D11_TEXTURE2D_DESC desc;

};
