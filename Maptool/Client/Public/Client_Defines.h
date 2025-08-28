#pragma once


#include <process.h>
#include "../Default/framework.h"

namespace Client
{
	const unsigned int			g_iWinSizeX = 1280;
	const unsigned int			g_iWinSizeY = 720;

	enum class LEVEL { STATIC, LOADING, LOGO, GAMEPLAY, END };
	enum class ADD_TYPE { PLAYER, MONSTER, YGGDRASIL, TREE, ROCK, TERRAIN_INCREASE, TERRAIN_DECREASE, END };
}

using namespace Client;

extern HINSTANCE g_hInstance;
extern HWND g_hWnd;
