#pragma once

#include "Hero.h"
#include "Bandit.h"

class Maze
{
public:
	static const int SizeX = 28;
	static const int SizeY = 36;

	Maze();
	int getTileCode(int x, int y);

	bool tileBody(int x, int y);
	bool isIntersection(int x, int y);

	void removeCoin(Hero* hero, Bandit* bandit1, Bandit* bandit2, Bandit* bandit3, Bandit* bandit4);

private:
	int tiles[SizeX][SizeY];
};

