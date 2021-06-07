#include "Body.h"

#include <cmath>

Body::Body(int tilePosX, int tilePosY)
{
	tileX = tilePosX;
	tileY = tilePosY;
	screenPosX = tilePosX * 16.0f + 8.0f + 8.0f;
	screenPosY = tilePosY * 16.0f + 8.0f;
}

float Body::getScreenPosX()
{
	return screenPosX;
}

float Body::getScreenPosY()
{
	return screenPosY;
}

int Body::getTileX()
{
	return tileX;
}

int Body::getTileY()
{
	return tileY;
}

void Body::move(float x, float y)
{
	screenPosX += x;
	screenPosY += y;

	if ((int)(screenPosX + 8) % 16 == 0 && (int)(screenPosY + 8) % 16 == 0)
	{
		tileX = (int)round((screenPosX - 8) / 16);
		tileY = (int)round((screenPosY - 8) / 16);
	}
}

void Body::spawn(int x, int y)
{
	tileX = x;
	tileY = y;
	screenPosX = x * 16.0f + 8.0f;
	screenPosY = y * 16.0f + 8.0f;
}
