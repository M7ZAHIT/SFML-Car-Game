#include "Rock.h"

void Rock::initVariables()
{
	this->pointCount = rand() % 5+3; //min = 3 max = 8
	this->type = 0;
	this->speed = static_cast<float>(this->pointCount / 4);
	this->damage = this->pointCount;
	
}

void Rock::initShape()
{
	this->shape.setRadius(this->pointCount * 5);
	this->shape.setPointCount(this->pointCount);
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

Rock::Rock(float pos_x, float pos_y)
{
	this->initVariables();
	this->initShape();

	this->shape.setPosition(pos_x, pos_y);
}

Rock::~Rock()
{

}

//Accessors
const sf::FloatRect Rock::getBounds() const
{
	return this->shape.getGlobalBounds();
}


const int& Rock::getDamage() const
{
	return this->damage;
}

int Rock::getPointCount()
{
	return (int)this->pointCount;
}

//Functions
void Rock::update()
{
	this->shape.move(0.f, this->speed);
}

void Rock::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
