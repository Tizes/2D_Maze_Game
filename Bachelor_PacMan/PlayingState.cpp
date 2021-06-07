#include "PlayingState.h"

#include "SFML/Graphics.hpp"

#include "Hero.h"
#include "Bandit.h"
#include "Resources.h"
#include "Directions.h"


#include <cmath>
#include <random>
#include <cstdlib>

using namespace sf;

void PlayingState::init()
{
	console = new Console("PlayingState");

	maze = new Maze();

	hero = new Hero();
	bandit1 = new Bandit(13, 14, 3, 4);
	bandit2 = new Bandit(13, 17, 23, 4);
	bandit3 = new Bandit(11, 17, 26, 32);
	bandit4 = new Bandit(15, 17, 1, 32);

	bandit1->spawn(13, 14);
	bandit2->spawn(13, 14);
	bandit3->spawn(13, 14);
	bandit4->spawn(13, 14);

	srand((unsigned int)time(NULL));

	console->writeLine("Init done");

	waitTime = 0;
}

void PlayingState::loop()
{
	if (heroCanMove() && !hero->isDead())
		hero->move();
	else
		hero->stop();

	if (maze->isIntersection(hero->getTileX(), hero->getTileY()))
		hero->stop();

	maze->removeCoin(hero, bandit1, bandit2, bandit3, bandit4);

	if (!hero->getDirections().empty())
	{
		if (!bandit1->isScattering())
			bandit1->setDestination(hero->getTileX(), hero->getTileY());

		if (!bandit2->isScattering())
		{
			switch (hero->getDirections().front())
			{
			case Direction::Up:
				bandit2->setDestination(hero->getTileX(), hero->getTileY() - 4);
				break;
			case Direction::Down:
				bandit2->setDestination(hero->getTileX(), hero->getTileY() + 4);
				break;
			case Direction::Left:
				bandit2->setDestination(hero->getTileX() - 4, hero->getTileY());
				break;
			case Direction::Right:
				bandit2->setDestination(hero->getTileX() + 4, hero->getTileY());
				break;
			}
		}

		if (!bandit3->isScattering())
			bandit3->setDestination(hero->getTileX() + (bandit1->getTileX() - hero->getTileX()), hero->getTileY() + (bandit1->getTileY() - hero->getTileY()));

		if (!bandit4->isScattering())
		{
			if (sqrt(pow((bandit4->getTileX() - (hero->getTileX())), 2) + pow((bandit4->getTileY() - (hero->getTileY())), 2)) < 9)
			{
				bandit4->setDestination(hero->getTileX(), hero->getTileY());
			}
			else
			{
				bandit4->setDestination(1, 32);
			}
		}
	}

	handleBanditMove(bandit1);
	handleBanditMove(bandit2);
	handleBanditMove(bandit3);
	handleBanditMove(bandit4);

	



	handleBanditAttack(bandit1);
	handleBanditAttack(bandit2);
	handleBanditAttack(bandit3);
	handleBanditAttack(bandit4);

	if (hero->getCoinsTaken() == 10)
	{
		bandit1->spawn(-2, -2);
		bandit2->spawn(-2, -2);
		bandit3->spawn(-2, -2);
		bandit4->spawn(-2, -2);
		waitTime++;
	}

	if (hero->isDead())
		waitTime++;

	if (waitTime == 400)
	{
		if (hero->isDead())
		{
			if (bandit1->isOutOfSpawn()) bandit1->spawn(13, 14);
			if (bandit2->isOutOfSpawn()) bandit2->spawn(13, 14);
			if (bandit3->isOutOfSpawn()) bandit3->spawn(13, 14);
			if (bandit4->isOutOfSpawn()) bandit4->spawn(13, 14);
			hero->spawn(13, 26);
			hero->setDead(false);
			waitTime = 0;
		}
		else
		{
			PlayingState::init();
			waitTime = 0;
		}
	}
}

void PlayingState::render(RenderWindow* window)
{
	Sprite heroSprite;
	Sprite bandit1Sprite;
	Sprite bandit2Sprite;
	Sprite bandit3Sprite;
	Sprite bandit4Sprite;

	if (hero->getDirections().empty())
		heroSprite = *Resources::get(Resources::Hero, false, Direction::Unset);
	else
		heroSprite = *Resources::get(Resources::Hero, true, hero->getDirections().front());

	if (hero->isDead())
		heroSprite = *Resources::get(Resources::DeadHero, true, Direction::Unset);


		bandit1Sprite = *Resources::get(Resources::Bandit1, bandit1->isOutOfSpawn(), bandit1->getDirection());
		bandit2Sprite = *Resources::get(Resources::Bandit2, bandit2->isOutOfSpawn(), bandit2->getDirection());
		bandit3Sprite = *Resources::get(Resources::Bandit3, bandit3->isOutOfSpawn(), bandit3->getDirection());
		bandit4Sprite = *Resources::get(Resources::Bandit4, bandit4->isOutOfSpawn(), bandit4->getDirection());
	

		heroSprite.setPosition(hero->getScreenPosX(), hero->getScreenPosY());
		bandit1Sprite.setPosition(bandit1->getScreenPosX(), bandit1->getScreenPosY());
		bandit2Sprite.setPosition(bandit2->getScreenPosX(), bandit2->getScreenPosY());
		bandit3Sprite.setPosition(bandit3->getScreenPosX(), bandit3->getScreenPosY());
		bandit4Sprite.setPosition(bandit4->getScreenPosX(), bandit4->getScreenPosY());

	for (int i = 0; i < Maze::SizeX; i++)
	{
		for (int j = 0; j < Maze::SizeY; j++)
		{
			Resources::MazeParts[maze->getTileCode(i, j)]->setPosition(i * 16.0f, j * 16.0f);
			window->draw(*Resources::MazeParts[maze->getTileCode(i, j)]);
		}
	}

	window->draw(heroSprite);
	window->draw(bandit1Sprite);
	window->draw(bandit2Sprite);
	window->draw(bandit3Sprite);
	window->draw(bandit4Sprite);
}

void PlayingState::keyPressed(int code)
{
	switch (code)
	{
	case Keyboard::Up:
		hero->queueDirection(Direction::Up);
		break;
	case Keyboard::Down:
		hero->queueDirection(Direction::Down);
		break;
	case Keyboard::Left:
		hero->queueDirection(Direction::Left);
		break;
	case Keyboard::Right:
		hero->queueDirection(Direction::Right);
		break;
	}
}

void PlayingState::keyReleased(int code)
{

}

bool PlayingState::heroCanMove()
{
	if (!hero->getDirections().empty())
	{
		switch (hero->getDirections().front())
		{
		case Direction::Up:
			return !maze->tileBody(hero->getTileX(), hero->getTileY() - 1);
			break;
		case Direction::Down:
			return !maze->tileBody(hero->getTileX(), hero->getTileY() + 1);
			break;
		case Direction::Left:
			return !maze->tileBody(hero->getTileX() - 1, hero->getTileY());
			break;
		case Direction::Right:
			return !maze->tileBody(hero->getTileX() + 1, hero->getTileY());
			break;
		}
	}
	return true;
}

void PlayingState::handleBanditMove(Bandit* bandit)
{
	if (bandit->isScattering())
	{
		if (bandit->getTileX() == bandit->getDestX() && bandit->getTileY() == bandit->getDestY())
		{
			bandit->setScattering(false);
		}
	}

	if (maze->isIntersection(bandit->getTileX(), bandit->getTileY()))
	{
		if (bandit->shouldTakeDecision())
		{
			float dRight = calculateDistance(bandit, 1, 0);
			float dLeft = calculateDistance(bandit, -1, 0);
			float dUp = calculateDistance(bandit, 0, -1);
			float dDown = calculateDistance(bandit, 0, 1);

			if (dRight < dLeft && dRight < dUp && dRight < dDown)
				bandit->setDirection(Direction::Right);
			else if (dLeft < dRight && dLeft < dUp && dLeft < dDown)
				bandit->setDirection(Direction::Left);
			else if (dUp < dLeft && dUp < dRight && dUp < dDown)
				bandit->setDirection(Direction::Up);
			else if (dDown < dLeft && dDown < dUp && dDown < dRight)
				bandit->setDirection(Direction::Down);
		}
		bandit->setTakeDecision(false);
	}
	else
	{
		bandit->setTakeDecision(true);
	}
	if (banditCanMove(bandit) && bandit->isOutOfSpawn())
		bandit->move();
	else
		bandit->setTakeDecision(true);
}

bool PlayingState::banditCanMove(Bandit* bandit)
{
	switch (bandit->getDirection())
	{
	case Direction::Up:
		return !maze->tileBody(bandit->getTileX(), bandit->getTileY() - 1);
		break;
	case Direction::Down:
		return !maze->tileBody(bandit->getTileX(), bandit->getTileY() + 1);
		break;
	case Direction::Left:
		return !maze->tileBody(bandit->getTileX() - 1, bandit->getTileY());
		break;
	case Direction::Right:
		return !maze->tileBody(bandit->getTileX() + 1, bandit->getTileY());
		break;
	default:
		return false;
	}
}

float PlayingState::calculateDistance(Bandit* bandit, int addX, int addY)
{
	float distance = 1000000.0f;
	if (!maze->tileBody(bandit->getTileX() + addX, bandit->getTileY() + addY))
	{
		distance = (float)sqrt(pow((bandit->getDestX() - (bandit->getTileX() + addX)), 2) + pow((bandit->getDestY() - (bandit->getTileY() + addY)), 2));
	}
	return distance;
}

void PlayingState::handleBanditAttack(Bandit* bandit)
{
	if (hero->getTileX() == bandit->getTileX() && hero->getTileY() == bandit->getTileY())
	{
		
			hero->setDead(true);
			bandit1->spawn(-2, -2);
			bandit2->spawn(-2, -2);
			bandit3->spawn(-2, -2);
			bandit4->spawn(-2, -2);

	}
}