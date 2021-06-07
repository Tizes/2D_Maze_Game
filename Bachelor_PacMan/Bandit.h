#pragma once

#include "Body.h"

#include "Directions.h"

class Bandit :
	public Body
{
private:
	int destinationTileX;
	int destinationTileY;
	Direction moving;

	bool scattering;
	bool outOfSpawn;

	bool decision;



public:
	Bandit(int tilePosX, int tilePosY, int destinationX, int destinationY);

	void setDestination(int x, int y);
	int getDestX();
	int getDestY();

	void setDirection(Direction dir);
	Direction getDirection();
	void move();

	bool isScattering();
	void setScattering(bool s);

	bool isOutOfSpawn();

	bool shouldTakeDecision();
	void setTakeDecision(bool d);

	void spawn(int x, int y);


};

