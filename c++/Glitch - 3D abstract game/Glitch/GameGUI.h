#pragma once

#include <string>
#include "DirectXTK\SimpleMath.h"
#include "DirectXTK/SpriteBatch.h"
#include "DirectXTK/SpriteFont.h"
#include "Texture.h"

#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

namespace GameGUI
{
	void drawCrosshair(SpriteBatch* sb, Texture* crosshair);
	void drawHp(SpriteBatch* sb, Player* player, Texture* last, Texture* sLast, Texture* green, Texture* orange, Texture* red);
	void drawNextLevel(SpriteBatch* sb, Texture* level, float levelTimer);
	void displayDetails(SpriteBatch* sb, SpriteFont* sf, int currentLevel, int score, int maxMonsters, int lateSpawnMonsters, int monstersKilled);
}