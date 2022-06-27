#include "Entity.h"

void Entity::initVariables()
{
	this->movementComponent = NULL;
}

Entity::Entity()
{
	this->initVariables();
}
Entity::~Entity() 
{
	delete this->movementComponent;
}

void Entity::setTexture(sf::Texture& texture, sf::Vector2f scale)
{
	this->sprite.setTexture(texture);
	this->sprite.setScale(scale);
}
void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}
void Entity::setPosition(const float x, const float y)
{
	this->sprite.setPosition(sf::Vector2f(x, y));
}
void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y, dt);
	}
}
void Entity::update(const float& dt)
{
	if (this->movementComponent)
		this->movementComponent->update(dt);
}
void Entity::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
