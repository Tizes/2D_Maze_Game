#pragma once
#include "GameState.h"

#include "Console.h"
#include "Body.h"
#include "Hero.h"
#include "Bandit.h"
#include "Maze.h"

class PlayingState :
	public GameState
{
private:
	Console* console;
	Maze* maze;
	Hero* hero;
	Bandit* bandit1;
	Bandit* bandit2;
	Bandit* bandit3;
	Bandit* bandit4;

	int waitTime;

	bool heroCanMove();
	void handleBanditMove(Bandit* bandit);
	bool banditCanMove(Bandit* bandit);
	float calculateDistance(Bandit* bandit, int addX, int addY);

	void handleBanditAttack(Bandit* bandit);

public:
	void init();
	void loop();
	void render(sf::RenderWindow* window);
	void keyPressed(int code);
	void keyReleased(int code);
};

