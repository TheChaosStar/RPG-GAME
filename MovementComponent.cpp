#include "MovementComponent.h"

MovementComponent::MovementComponent(
	sf::Sprite& sprite,
	float maxVelocity,
	float acceleration,
	float deceleration
) : 
	sprite(sprite),
	maxVelocity(maxVelocity),
	acceleration(acceleration),
	deceleration(deceleration)
{
}
MovementComponent::~MovementComponent()
{
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	// Acceleration
	this->velocity.x += this->acceleration * dir_x;
	this->velocity.y += this->acceleration * dir_y;
}
void MovementComponent::update(const float& dt)
{
	if (this->velocity.x > 0.f) // Check for position X
	{
		// Max velocity check
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		// Deceleration
		this->velocity.x -= this->deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}
	else if (this->velocity.x < 0.f) // Check for negative X
	{
		// Max velocity check
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		// Deceleration
		this->velocity.x += this->deceleration;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}

	if (this->velocity.y > 0.f) // Check for position Y
	{
		// Max velocity check
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;

		// Deceleration
		this->velocity.y -= this->deceleration;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
	}
	else if (this->velocity.y < 0.f) // Check for negative Y
	{
		// Max velocity check
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;

		// Deceleration
		this->velocity.y += this->deceleration;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}

	// final move
	this->sprite.move(this->velocity * dt);
}