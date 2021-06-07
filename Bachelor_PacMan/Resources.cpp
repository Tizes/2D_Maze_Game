#include "Resources.h"

std::map<int, sf::Sprite*> Resources::sprites;
std::map<int, Animation> Resources::animations;

sf::Texture Resources::Things;
sf::Texture Resources::Maze;
Console Resources::Console("Resources");

sf::Sprite* Resources::MazeParts[32];

const int Resources::Hero = 0;
const int Resources::HeroDown = 1;
const int Resources::HeroLeft = 2;
const int Resources::HeroRight = 3;
const int Resources::Bandit1 = 4;
const int Resources::Bandit1Down = 5;
const int Resources::Bandit1Left = 6;
const int Resources::Bandit1Right = 7;
const int Resources::Bandit2 = 8;
const int Resources::Bandit2Down = 9;
const int Resources::Bandit2Left = 10;
const int Resources::Bandit2Right = 11;
const int Resources::Bandit3 = 12;
const int Resources::Bandit3Down = 13;
const int Resources::Bandit3Left = 14;
const int Resources::Bandit3Right = 15;
const int Resources::Bandit4 = 16;
const int Resources::Bandit4Down = 17;
const int Resources::Bandit4Left = 18;
const int Resources::Bandit4Right = 19;

const int Resources::DeadHero = 20;

void Resources::load()
{
	Maze.loadFromFile("textures/maze.png");

	int index = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			MazeParts[index] = new sf::Sprite(Maze, sf::IntRect(i * 8, j * 8, 8, 8));
			MazeParts[index]->setScale(2.0f, 2.0f);
			index++;
		}
	}

	Things.loadFromFile("textures/Chars_sprites.png");

	loadSprite(Resources::Hero, 94, 32, 0);
	loadSprite(Resources::HeroDown, 0, 32, 0);
	loadSprite(Resources::HeroLeft, 63, 32, 0);
	loadSprite(Resources::HeroRight, 32, 32, 0);
	loadSprite(Resources::Bandit1, 94, 0, 0);
	loadSprite(Resources::Bandit1Down, 0, 0, 0);
	loadSprite(Resources::Bandit1Left, 63, 0, 0);
	loadSprite(Resources::Bandit1Right, 32, 0, 0);
	loadSprite(Resources::Bandit2, 94, 0, 0);
	loadSprite(Resources::Bandit2Down, 0, 0, 0);
	loadSprite(Resources::Bandit2Left, 63, 0, 0);
	loadSprite(Resources::Bandit2Right, 32, 0, 0);
	loadSprite(Resources::Bandit3, 94, 0, 0);
	loadSprite(Resources::Bandit3Down, 0, 0, 0);
	loadSprite(Resources::Bandit3Left, 63, 0, 0);
	loadSprite(Resources::Bandit3Right, 32, 0, 0);
	loadSprite(Resources::Bandit4, 94, 0, 0);
	loadSprite(Resources::Bandit4Down, 0, 0, 0);
	loadSprite(Resources::Bandit4Left , 63, 0, 0);
	loadSprite(Resources::Bandit4Right, 32, 0, 0);

	loadSprite(Resources::DeadHero, 0, 75, 12);

	

	Console.writeLine("Finished creating sprites");
}

sf::Sprite* Resources::get(int value, bool animated, Direction facing)
{
	
		switch (facing)
		{
		case Direction::Down:
			value += 1;
			break;
		case Direction::Left:
			value += 2;
			break;
		case Direction::Right:
			value += 3;
			break;
		}
	

	if (animated)
	{
		animations.at(value).changeFrame();
		sprites.at(value)->setTextureRect(animations.at(value).getBounds());
	}

	return sprites.at(value);
}


void Resources::loadSprite(int value, int rect1, int rect2, int animationframes)
{
	sf::IntRect* rect = new sf::IntRect(rect1, rect2, 30, 30);
	sf::Sprite* sprite = new sf::Sprite(Things, *rect);
	sprite->setScale(1.5f, 1.5f);
	sprite->setOrigin(20.0f, 20.0f);
	sprites.insert(std::pair<int, sf::Sprite*>(value, sprite));
	animations.insert(std::pair<int, Animation>(value, Animation(rect, animationframes)));
}