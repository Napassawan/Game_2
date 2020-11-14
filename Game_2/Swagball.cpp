#include "Swagball.h"

void Swagball::initShape(const sf::RenderWindow&  window)
{	
	
	this->M1.setRadius(static_cast<float>(rand() % 10 + 10));

	sf::Color color;
	switch (this->type)
	{
	case DEFAULT:
		color = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
		break;
	case DAMAGING:
		color = sf::Color::Red;
		this->M1.setOutlineColor(sf::Color::White);
		this->M1.setOutlineThickness(3.f);
		break;
	case HEALING:
		color = sf::Color::Magenta;
		this->M1.setOutlineColor(sf::Color::White);
		this->M1.setOutlineThickness(3.f);
		break;
	}
	this->M1.setFillColor(color);
	this->M1.setPosition(sf::Vector2f(
		static_cast<float>(random_between(40, 860)),
		static_cast<float>(random_between(150, 550))
	)
	);
}

Swagball::Swagball(const sf::RenderWindow& window, int type)
	:type(type)
{
		this->initShape(window);
}

Swagball::~Swagball()
{
}

const sf::CircleShape Swagball::getShape() const
{
	return this->M1;
}

const int& Swagball::getType() const
{
	return this -> type;
}

void Swagball::update()
{

}

void Swagball::render(sf::RenderTarget & target)
{
	target.draw(this->M1);
}
