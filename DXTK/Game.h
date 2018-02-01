#pragma once

#include "DrawData2D.h"
#include "GameData.h"
#include "StepTimer.h"
#include <d3d11.h>
#include <memory>
#include <vector>

struct DrawData2D;
struct GameData;
class FollowCamera;
class Player;

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final
{
public:

    Game(ID3D11Device* _pd3dDevice, HWND _hWnd, HINSTANCE _hInstance);
	~Game();

    // Basic game loop
    bool Tick();
	void Draw(ID3D11DeviceContext* _pd3dImmediateContext);

private:
    // Device resources.
	DWORD play_time; //amount of time since the game started
	HWND        hWnd;

	// Game Objects
	GameData game_data;
	DrawData2D draw_data;

	std::vector<Player*> tiles;
	std::unique_ptr<FollowCamera> camera = nullptr;
};