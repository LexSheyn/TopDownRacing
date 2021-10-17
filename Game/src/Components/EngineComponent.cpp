#include "../stdafx.h"
#include "EngineComponent.h"

// Constructors and Destructor:

EngineComponent::EngineComponent(sf::Sprite& sprite, sf::RectangleShape& hitbox, const float speedMax, const float boostMax, const float deceleration)
	: Sprite(sprite), Hitbox(hitbox), Pi(3.141592f)
{
	InitVariables();

	Deceleration = deceleration;

	SpeedMax = speedMax;

	BoostMax = boostMax;

	Boost = 0.f;
}

EngineComponent::~EngineComponent()
{
}


// Functions:

void EngineComponent::Drive(const float& dt)
{
	Boost = BoostMax * dt;

	Angle = Sprite.getRotation();
}

void EngineComponent::Reverse(const float& dt)
{
	Boost = -BoostMax * dt;

	Angle = Sprite.getRotation();
}

void EngineComponent::TurnLeft(const float& dt)
{
	Sprite.rotate(-100.f * dt);
}

void EngineComponent::TurnRight(const float& dt)
{
	Sprite.rotate(100.f * dt);
}

void EngineComponent::InvertVelocity()
{
	Velocity = -Velocity / 3.f;
}

void EngineComponent::InvertVelocityX()
{
	Velocity.x = -Velocity.x / 3.f;
}

void EngineComponent::InvertVelocityY()
{
	Velocity.y = -Velocity.y / 3.f;
}

const bool EngineComponent::CheckStatus(Status status) const
{
	switch (status)
	{
		case Status::Idle:
		{
			if (Velocity.x == 0.f && Velocity.y == 0.f)
			{
				return true;				
			}

			break;
		}

		case Status::Driving:
		{
			if (Velocity.x != 0.f || Velocity.y != 0.f)
			{
				return true;				
			}

			break;
		}
	}

	return false;
}

void EngineComponent::Update(const float& dt)
{
	// Acceleration calculation
	Acceleration.x =  std::sin(Angle * Pi / 180.f) * Boost;
	Acceleration.y = -std::cos(Angle * Pi / 180.f) * Boost;

	// Velocity calculation
	Velocity += Acceleration;

	// X
	if (Velocity.x > 0.f)
	{
		if (Velocity.x > SpeedMax)
		{
			Velocity.x = SpeedMax;
		}

		Velocity.x -= Deceleration * dt;

		if (Velocity.x < 0.f)
		{
			Velocity.x = 0.f;
		}
	}
	else if (Velocity.x < 0.f)
	{
		if (Velocity.x < -SpeedMax)
		{
			Velocity.x = -SpeedMax;
		}

		Velocity.x += Deceleration * dt;

		if (Velocity.x > 0.f)
		{
			Velocity.x = 0.f;
		}
	}

	// Y
	if (Velocity.y > 0.f)
	{
		if (Velocity.y > SpeedMax)
		{
			Velocity.y = SpeedMax;
		}

		Velocity.y -= Deceleration * dt;

		if (Velocity.y < 0.f)
		{
			Velocity.y = 0.f;
		}
	}
	else if (Velocity.y < 0.f)
	{
		if (Velocity.y < -SpeedMax)
		{
			Velocity.y = -SpeedMax;
		}

		Velocity.y += Deceleration * dt;

		if (Velocity.y > 0.f)
		{
			Velocity.y = 0.f;
		}
	}	

	// Resetting boost value
	Boost = 0.f;
	
	// Final move
	Hitbox.move(Velocity * dt);
}


// Accessors:

const float& EngineComponent::GetBoost() const
{
	return Boost;
}

const float& EngineComponent::GetSpeedMax() const
{
	return SpeedMax;
}

const sf::Vector2f& EngineComponent::GetVelocity() const
{
	return Velocity;
}


// Private Functions:

void EngineComponent::InitVariables()
{
	Angle = 0.f;
}
