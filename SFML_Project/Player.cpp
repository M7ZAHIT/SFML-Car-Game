#include "Player.h"

void Player::setName(std::string enteredName)
{
	this->name = enteredName;
}

std::string Player::getName()
{
	return this->name;
}

void Player::initVariables()
{	
	this->movementSpeed = 2.f;

	this->hpMax = 100;
	this->hp = this->hpMax;
}

void Player::initTexture()
{
	//Load a texture from file
	this->texture.loadFromFile("Figures/car2.png");
}

void Player::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);

	//Resize the sprite
	this->sprite.scale(0.2f, 0.2f);
}

Player::Player()
{
	this->setPosition(400, 600.f);
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{

}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
}

void Player::goUp()
{
	move(0.f, -1.f);
}

void Player::goDown()
{
	move(0.f, 1.f);
}

void Player::goLeft()
{
	move(-1.f, 0.f);
}

void Player::goRight()
{
	move(1.f, 0.f);
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}





void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
