#include "Game.h"

void Game::initVariables()
{
	this->endGame = false;
	this->spawnTimerMax = 20.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxSwagBalls = 15;
	this->points = 0;
}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(900, 600);
	this->window = new sf::RenderWindow(this->videoMode, "The Collector",sf::Style::Close | sf::Style::Titlebar);
	auto image = sf::Image{};
	if (!image.loadFromFile("img/icon.png"))
	{
		printf_s("ERROR::GAME::ICON");
	}
	this->window->setIcon(64, 64, image.getPixelsPtr());
	this->window->setVerticalSyncEnabled(true);
	this->window->setFramerateLimit(60);

}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("img/bg.png"))
	{
		printf("ERROR::GAME::BACKGROUND");
	}

	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initSky()
{
	if (!this->worldSkyTex.loadFromFile("img/sky.png"))
	{
		printf("ERROR::GAME::SKY");
	}
	worldSkyTex.setRepeated(true);
	this->parallaxShader.loadFromMemory(
		"uniform float offset;"

		"void main() {"
		"    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
		"    gl_TexCoord[0] = -gl_TextureMatrix[0] * gl_MultiTexCoord0;"
		"    gl_TexCoord[0].x = gl_TexCoord[0].x + offset;" // magic
		"    gl_FrontColor = gl_Color;"
		"}"
		, sf::Shader::Vertex);
	
	this->worldSky.setTexture(this->worldSkyTex);
}

void Game::initFont()
{
	if (!this->font.loadFromFile("font/FSEX300.ttf"))
	{
		printf_s("ERROR::GAME::INITFONT");
	}
}

void Game::initText()
{
	this->guiText.setFont(this->font);
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setCharacterSize(25);

	this->endGameText.setFont(this->font);
	this->endGameText.setFillColor(sf::Color::Red);
	this->endGameText.setCharacterSize(60);
	this->endGameText.setPosition(300, 300);
	this->endGameText.setString("GAMEOVER");
}


Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initSky();
	this->initWorld();
	this->initFont();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}

const bool& Game::getEndGame() const
{
	return this->endGame;
}

const bool Game::running() const
{
	return this->window->isOpen() /*this->endGame == false*/;
}

void Game::pollEvent()
{
	while (this->window->pollEvent(this->sfmlEvent))
	{
		switch (this->sfmlEvent.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::spawnSwagBalls()
{
	if (this->spawnTimer < this->spawnTimerMax)
		this->spawnTimer += 1.f;
	else
	{
		if (this->swagBalls.size() < this->maxSwagBalls)
		{
			this->swagBalls.push_back(Swagball(*this->window, this->randomballType()));

			this->spawnTimer = 0.f;
		}
			
	}
}

const int Game::randomballType() const
{
	int type = SwagBallTypes::DEFAULT;

	int randValue = rand() % 100 + 1;
	if (randValue > 60 && randValue <= 80)
		type = SwagBallTypes::DAMAGING;
	else if (randValue > 80 && randValue <= 100)
		type = SwagBallTypes::HEALING;

	return type;
}

void Game::updatePlayer()
{
	this->player.update(this->window);

	if (this->player.getHp() <= 0)
		this->endGame = true;
}

void Game::updateCollision()
{
	for (size_t i = 0; i < this->swagBalls.size(); i++)
	{
		if (this->player.getShape().getGlobalBounds().intersects(this->swagBalls[i].getShape().getGlobalBounds()))
		{
			switch (this->swagBalls[i].getType())
			{
			case SwagBallTypes::DEFAULT:
				this->points = points + 50;
				break;
			case SwagBallTypes::DAMAGING:
				this->player.takeDamage(2);
				this->points = points - 100;
				break;
			case SwagBallTypes::HEALING:
				this->player.gainHealth(1);
				this->points = points + 50;
				break;
			}
			
			this->swagBalls.erase(this->swagBalls.begin() + i);
		}
	}
}

void Game::updateGUI()
{
	std::stringstream ss;

	ss << " Points : " << this->points << "\n" << " Health : " << this->player.getHp() << " / " << this->player.getHpMax() << "\n";

	this->guiText.setString(ss.str());
}

void Game::updateWorld()
{
}

void Game::update()
{
	this->pollEvent();
	
	if (this->endGame == false)
	{
		this->spawnSwagBalls();
		this->updatePlayer();
		this->updateCollision();
		this->updateGUI();
		this->updateWorld();
	}
}

void Game::renderGUI(sf::RenderTarget* target)
{
	target->draw(this->guiText);
}

void Game::renderSky()
{
	parallaxShader.setUniform("offset", offset += clockbg.restart().asSeconds() / 50);
	this->window->draw(this->worldSky, &parallaxShader);
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::render()
{
	this->window->clear();
	this->renderSky();
	this->renderWorld();
	this->player.render(this->window);
	
	for (auto i : this->swagBalls)
	{
		i.render(*this->window);
	}

	this->renderGUI(this->window);

	if (this->endGame == true)
		this->window->draw(this->endGameText);

	this->window->display();
}
