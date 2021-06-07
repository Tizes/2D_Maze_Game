#include "Bandit.h"

Bandit::Bandit(int tilePosX, int tilePosY, int destinationX, int destinationY) : Body(tilePosX, tilePosY)
{
	setDestination(destinationX, destinationY);
	setDirection(Direction::Unset);
	scattering = true;
	outOfSpawn = false;
	decision = true;

}

void Bandit::setDestination(int x, int y)
{
	destinationTileX = x;
	destinationTileY = y;
}

int Bandit::getDestX()
{
	return destinationTileX;
}

int Bandit::getDestY()
{
	return destinationTileY;
}

void Bandit::setDirection(Direction dir)
{
	moving = dir;
}

Direction Bandit::getDirection()
{
	return moving;
}

void Bandit::move()
{
	switch (moving)
	{
	case Direction::Up:
		Body::move(0, -0.2f);
		break;
	case Direction::Down:
		Body::move(0, 0.2f);
		break;
	case Direction::Left:
		Body::move(-0.2f, 0);
		break;
	case Direction::Right:
		Body::move(0.2f, 0);
		break;
	}
}

bool Bandit::isScattering()
{
	return scattering;
}

void Bandit::setScattering(bool s)
{
	scattering = s;
}

bool Bandit::isOutOfSpawn()
{
	return outOfSpawn;
}

bool Bandit::shouldTakeDecision()
{
	return decision;
}

void Bandit::setTakeDecision(bool d)
{
	decision = d;
}

void Bandit::spawn(int x, int y)
{
	Body::spawn(x, y);
	outOfSpawn = true;
}


