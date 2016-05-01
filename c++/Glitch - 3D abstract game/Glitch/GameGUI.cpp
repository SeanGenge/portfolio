#include "GameGUI.h"

namespace GameGUI
{
	void displayDetails(SpriteBatch* sb, SpriteFont* sf, int currentLevel, int score, int maxMonsters, int lateSpawnMonsters, int monstersKilled)
	{
		std::wstring l = L"Level: " + std::to_wstring(currentLevel);
		std::wstring s = L"Score: " + std::to_wstring(score);
		std::wstring m = L"Enemies left: " + std::to_wstring((maxMonsters + lateSpawnMonsters) - monstersKilled);

		sf->DrawString(sb, l.c_str(), Vector2(780, 15), Colors::DarkGreen);
		sf->DrawString(sb, s.c_str(), Vector2(780, 45), Colors::DarkGreen);
		sf->DrawString(sb, m.c_str(), Vector2(780, 75), Colors::DarkGreen);
	}

	void drawCrosshair(SpriteBatch* sb, Texture* crosshair)
	{
		RECT middle;
		int size = 25;
		//Hard coded middle of the screen.
		middle.left = 512 - size;
		middle.right = 512 + size;
		middle.top = 387 - size;
		middle.bottom = 387 + size;

		sb->Draw(crosshair->GetShaderResourceView(), middle, Colors::Aquamarine);
	}

	void drawHp(SpriteBatch* sb, Player* player, Texture* last, Texture* sLast, Texture* green, Texture* orange, Texture* red)
	{
		float percentage = (float)player->getHealth() / (float)player->getMaxHealth();
		//Padding for the border
		int padding = 8;

		RECT backBlackRect;
		backBlackRect.left = 10;
		backBlackRect.right = 400;
		backBlackRect.top = 710;
		backBlackRect.bottom = 760;

		RECT mainRect = backBlackRect;
		mainRect.left += padding;
		mainRect.right -= padding;
		mainRect.top += padding;
		mainRect.bottom -= padding;

		//To make the black border look even, need to add 5 pixels as well
		backBlackRect.right += 5;

		//Renders the hp bar at the bottom left corner. Does this in layers
		//Border
		sb->Draw(last->GetShaderResourceView(), backBlackRect);
		//Gray part behind the health meter (green, orange or red)
		sb->Draw(sLast->GetShaderResourceView(), mainRect);

		//Resize the mainRect for the health depending on how much hp is left
		mainRect.right *= percentage;
		//When health is very low, display a few pixels of that colour
		mainRect.right += 5;

		//Draws the actual hp colour depending on the percentage of hp left
		if (percentage > 0.80)
		{
			//Green
			sb->Draw(green->GetShaderResourceView(), mainRect);
		}
		else if (percentage > 0.25 && percentage <= 0.80)
		{
			//Orange
			sb->Draw(orange->GetShaderResourceView(), mainRect);
		}
		else if (percentage <= 0.25)
		{
			//Red
			sb->Draw(red->GetShaderResourceView(), mainRect);
		}
	}

	void drawNextLevel(SpriteBatch* sb, Texture* level, float levelTimer)
	{
		int paddingLeftRight = 150;
		int paddingTopBottom = 75;
		int centerX = 520;
		int centerY = 580;
		RECT rect;
		rect.left = centerX - paddingLeftRight;
		rect.right = centerX + paddingLeftRight;
		rect.top = centerY - paddingTopBottom + (levelTimer * 50);
		rect.bottom = centerY + paddingTopBottom + (levelTimer * 50);

		sb->Draw(level->GetShaderResourceView(), rect);
	}
}