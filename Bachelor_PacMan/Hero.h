#pragma once

#include "Body.h"

#include <queue>
#include "Directions.h"

class Hero
		: public Body
{
private:
	std::queue<Direction> directions;
	int takenCoins;
	bool dead;

public:
	Hero();

	void queueDirection(Direction dir);
	void move();
	std::queue<Direction> getDirections();
	void stop();

	void takeCoin();
	int getCoinsTaken();

	void setDead(bool d);
	bool isDead();
};

