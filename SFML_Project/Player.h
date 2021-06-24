#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float movementSpeed;

	std::string name;

	void setName(std::string enteredName);
	std::string getName();
	
	int hp;
	int hpMax;

	//Private functions
	void initVariables();
	void initTexture();
	void initSprite();
	void move(const float dirX, const float dirY);

public:
	Player();
	 ~Player();

	//Accessor
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;

	//Modifiers
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void setHp(const int hp);
	void loseHp(const int value);

	void goUp();
	void goDown();
	void goLeft();
	void goRight();

	void render(sf::RenderTarget& target);
};

