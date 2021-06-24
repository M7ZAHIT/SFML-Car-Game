#include "Game.h"

//Private functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(612, 600), "Survival", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initScreen()
{
	//Load font
	this->font.loadFromFile("Fonts/PixellettersFull.ttf");
	
	this->pointText.setPosition(530, 25.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(25);
	this->pointText.setFillColor(sf::Color::Black);
	this->pointText.setString(std::to_string(this->points));	
	
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 3.f ,
		this->window->getSize().y / 3.f );

	//Init player GUI
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::initPoints()
{
	this->points = 0;
}

void Game::initBackground()
{
	this->backgroundTexture.loadFromFile("Figures/road.jpg");
	this->background.setTexture(this->backgroundTexture);
}


void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initRocks()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

//Con/Des
Game::Game()
{
	this->initWindow();
	this->initPoints();
	this->initScreen();
	this->initBackground();
	this->initPlayer();
	this->initRocks();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete textures
	for (auto& i : this->textures)
	{
		delete i.second;
	}
	//Delete rocks
	for (auto* i : this->rocks)
	{
		delete i;
	}
}




//Functions
void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();

		if (this->player->getHp() > 0)
			this->update();

		this->render();
	}
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::updateInput()
{
	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->goLeft();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->goRight();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->goUp();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->goDown();
}

void Game::updateScreen()
{
	std::stringstream ss;
	ss << "Points: " << this->points;

	this->pointText.setString(ss.str());

	//Update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));
}

void Game::renderBackground()
{
	this->window->draw(this->background);
}


void Game::updateCollision()
{
	//Left  collision
	if (this->player->getBounds().left < 60.f)
	{
		this->player->setPosition(60.f, this->player->getBounds().top);
	}
	//Right  collison
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x-60.f)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width-60.f, this->player->getBounds().top);
	}

	//Top  collision
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}
	//Bottom  collision
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}



void Game::updateRocks()
{
	//Spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->rocks.push_back(new Rock(rand() % this->window->getSize().x - 20.f, -100.f));
		this->spawnTimer = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto* rock : this->rocks)
	{
		rock->update();
		
	
		//player rock collision
		if (rock->getPointCount()!=4 && rock->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->rocks.at(counter)->getDamage());
			delete this->rocks.at(counter);
			this->rocks.erase(this->rocks.begin() + counter);
		}

		++counter;
	}
}

void Game::updatePoints()
{
	unsigned counter = 0;
	for (auto* rock : this->rocks)
	{
		rock->update();


		//player point update
		if (rock->getPointCount() == 4 && rock->getBounds().intersects(this->player->getBounds()))
		{
			this->points += 4;
			delete this->rocks.at(counter);
			this->rocks.erase(this->rocks.begin() + counter);
		}

		++counter;
	}
}


void Game::update()
{
	this->updateInput();

	this->updateCollision();

	this->updateRocks();

	this->updateScreen();

	this->updatePoints();

	
}

void Game::renderScreen()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::render()
{
	this->window->clear();

	this->renderBackground();

	//Draw all the stuffs
	this->player->render(*this->window);

	
	for (auto* rock : this->rocks)
	{
		rock->render(this->window);
	}

	this->renderScreen();

	//Game over screen
	if (this->player->getHp() <= 0)
		this->window->draw(this->gameOverText);

	this->window->display();
}
