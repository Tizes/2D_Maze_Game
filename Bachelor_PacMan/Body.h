#pragma once


class Body
{
protected:
	float screenPosX;
	float screenPosY;
	int tileX;
	int tileY;

public:
	Body(int tilePosX, int tilePosY);

	float getScreenPosX();
	float getScreenPosY();
	int getTileX();
	int getTileY();

	void move(float x, float y);
	void spawn(int x, int y);
};

