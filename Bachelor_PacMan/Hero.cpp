#include "Hero.h"

Hero::Hero() : Body(13, 26)
{
	takenCoins = 0;
}

void Hero::queueDirection(Direction dir)
{
	if (!directions.empty())
	{
		if (dir == -directions.front())
		{
			std::queue<Direction> clear;
			std::swap(directions, clear);
		}
	}

	if (directions.size() < 2)
		directions.push(dir);
}

void Hero::move()
{
	if (!directions.empty())
	{
		switch (directions.front())
		{
		case Direction::Up:
			Body::move(0, -0.4f);
			break;
		case Direction::Down:
			Body::move(0, 0.4f);
			break;
		case Direction::Left:
			Body::move(-0.4f, 0);
			break;
		case Direction::Right:
			Body::move(0.4f, 0);
			break;
		}
	}
}

std::queue<Direction> Hero::getDirections()
{
	return directions;
}

void Hero::stop()
{
	if (directions.size() > 1)
	{
		if ((int)(screenPosX + 8) % 16 == 0 && (int)(screenPosY + 8) % 16 == 0)
		{
			switch (directions.front())
			{
			case Direction::Up:
				directions.pop();
				break;
			case Direction::Down:
				directions.pop();
				break;
			case Direction::Left:
				directions.pop();
				break;
			case Direction::Right:
				directions.pop();
				break;
			}
		}
	}
}

void Hero::takeCoin()
{
	takenCoins++;
}

int Hero::getCoinsTaken()
{
	return takenCoins;
}

void Hero::setDead(bool d)
{
	dead = d;
}

bool Hero::isDead()
{
	return dead;
}
