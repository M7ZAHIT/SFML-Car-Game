

#include<SFML/Graphics.hpp>

class Rock
{
private:
	unsigned pointCount;
	sf::CircleShape shape;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;

	void initVariables();
	void initShape();

public:
	Rock(float pos_x, float pos_y);
	 ~Rock();

	//Accessors
	const sf::FloatRect getBounds() const;
	const int& getDamage() const;

	int getPointCount();
	void update();
	void render(sf::RenderTarget* target);
};

 