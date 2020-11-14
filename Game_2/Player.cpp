#include "Player.h"


void Player::initVariables()
{
	this->movementSpeed = 7.f;
	this->hpMax = 10;
	this->hp = hpMax;

}

void Player::initShape()
{

	this->Char.setSize(sf::Vector2f(70.f, 100.f));
	/*if (!this->ChTex.loadFromFile("img/char1.png"))
	{
		printf_s("ERROR::GAME::CHAR");
	}
	this->Char.setTexture(&this->ChTex);*/
}

Player::Player(float x, float y)
{
	this->Char.setPosition(x, y);

	this->initVariables();
	this->initShape();
}

Player::~Player()
{
}

const sf::RectangleShape& Player::getShape() const
{
	return this->Char;
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

void Player::takeDamage(const int damage)
{
	if (this->hp > 0)
		this->hp -= damage;

	if (this->hp < 0)
		this->hp = 0;
}

void Player::gainHealth(const int health)
{
	if (this->hp < this->hpMax)
		this->hp += health;
	if (this->hp > this->hpMax)
		this->hp = this->hpMax;
}

void Player::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->Char.move(-this->movementSpeed , 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->Char.move(this->movementSpeed , 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->Char.move(0.f, -this->movementSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->Char.move(0.f, this->movementSpeed );
	}

}

void Player::updateCollision(const sf::RenderTarget* target)
{
	//L
	if (this->Char.getGlobalBounds().left <= 0.f)
		this->Char.setPosition(0.f, this->Char.getGlobalBounds().top);
	//R
	if (this->Char.getGlobalBounds().left + this->Char.getGlobalBounds().width >= target->getSize().x)
		this->Char.setPosition(target->getSize().x - this->Char.getGlobalBounds().width, this->Char.getGlobalBounds().top);
	//T
	if (this->Char.getGlobalBounds().top <= 80.f)
		this->Char.setPosition(this->Char.getGlobalBounds().left, 80.f);
	//B
	if (this->Char.getGlobalBounds().top + this->Char.getGlobalBounds().height >= target->getSize().y)
		this->Char.setPosition(this->Char.getGlobalBounds().left, target->getSize().y - this->Char.getGlobalBounds().height);
}

void Player::update(const sf::RenderTarget* target)
{
	this->updateInput();
	
	this->updateCollision(target);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->Char);
}

