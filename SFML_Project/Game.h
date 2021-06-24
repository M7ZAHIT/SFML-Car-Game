#pragma once

#include <map>
#include <string>
#include <sstream>
#include "Player.h"
#include "Rock.h"


class Game
{
private:
	//Window
	sf::RenderWindow* window;

	//Resources
	std::map<std::string, sf::Texture*> textures;
	

	//GUI
	sf::Font font;
	sf::Text gameOverText;
	sf::Text pointText;

	//Background
	sf::Texture backgroundTexture;
	sf::Sprite background;

	//Points
	int points;
	
	//Player
	Player* player;

	
	
	//PlayerGUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Rock*> rocks;

	
	void initWindow();
	
	void initScreen();
	void initPoints();
	void initBackground();
	void initPlayer();
	void initRocks();

public:
	Game();
	 ~Game();

	//Functions
	void run();

	void updatePollEvents();
	void updateInput();
	void updateScreen();
	void renderBackground();
	void updateCollision();
	void updateRocks();
	void updatePoints();
	void update();

	void renderScreen();
	
	void render();
};

