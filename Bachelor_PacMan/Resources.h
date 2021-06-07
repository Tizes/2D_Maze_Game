#pragma once

#include "SFML/Graphics.hpp"
#include "Console.h"

#include "Animations.h"

#include "Directions.h"

#include <map>

class Resources
{
private:
	static sf::Texture Things;
	static sf::Texture Maze;
	static Console Console;

	static std::map<int, sf::Sprite*> sprites;
	static std::map<int, Animation> animations;

	static void loadSprite(int value, int rect1, int rect2, int animationframes);

	static const int HeroDown;
	static const int HeroLeft;
	static const int HeroRight;
	static const int Bandit1Down;
	static const int Bandit1Left;
	static const int Bandit1Right;
	static const int Bandit2Down;
	static const int Bandit2Left;
	static const int Bandit2Right;
	static const int Bandit3Down;
	static const int Bandit3Left;
	static const int Bandit3Right;
	static const int Bandit4Down;
	static const int Bandit4Left;
	static const int Bandit4Right;

public:
	static void load();
	static sf::Sprite* get(int value, bool animated, Direction facing);

	static sf::Sprite* MazeParts[];

	static const int Hero;
	static const int Bandit1;
	static const int Bandit2;
	static const int Bandit3;
	static const int Bandit4;

	static const int DeadHero;
};

