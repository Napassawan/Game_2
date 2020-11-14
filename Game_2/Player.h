#pragma once

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include "Animation.h"

class Player
{
private:
	sf::RectangleShape Char;
	sf::Texture ChTex;

	float movementSpeed;
	int hp;
	int hpMax;

	void initVariables();
	void initShape();

public:
	Player();
	virtual ~Player();

	const sf::RectangleShape& getShape() const;
	const int& getHp() const;
	const int& getHpMax() const;

	void takeDamage(const int damage);
	void gainHealth(const int health);

	void updateInput();
	void updateCollision(const sf::RenderTarget* target);
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

