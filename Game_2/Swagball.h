#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

enum SwagBallTypes {DEFAULT = 0, DAMAGING, HEALING, NROFTYPES};

class Swagball
{
private:
	sf::CircleShape M1;
	sf::Texture M1Tex;
	int type;

	int random_between(int min, int max)
	{
		int r = (rand() / (float)RAND_MAX) * (max + 1) + min;
		return r > max ? max : r;
	}

	void initShape(const sf::RenderWindow& window);
public:
	Swagball(const sf::RenderWindow& window,int type);
	virtual ~Swagball();

	const sf::CircleShape getShape() const;
	const int& getType() const;

	void update();
	void render(sf::RenderTarget& target);
};

