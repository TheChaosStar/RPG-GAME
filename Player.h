#pragma once

#include "Entity.h"

class Player : public Entity
{
private:


	void initVariables();
	void initComponents();

public:
	Player(float x, float y, sf::Texture& texture, sf::Vector2f scale);
	virtual ~Player();

};

