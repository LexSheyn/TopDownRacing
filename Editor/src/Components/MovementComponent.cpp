#include "../stdafx.h"
#include "MovementComponent.h"

// Constructors and Destructor:

MovementComponent::MovementComponent(sf::Sprite& sprite, const float velocityMax, const float acceleration, const float deceleration)
	: EntitySprite(sprite), Pi(3.141592f), Coefficient(std::cos((45.f * Pi) / 180.f))
{
	// std::cos((45.f * this->pi) / 180.f) = 0.707107f;

	InitVariables();

	// Cartographic
	Acceleration[Cartographic] = acceleration;
	Deceleration[Cartographic] = deceleration;
	VelocityMax[Cartographic] = velocityMax;

	// Polar
	Acceleration[Polar] = Acceleration[Cartographic] * Coefficient;
	Deceleration[Polar] = Deceleration[Cartographic] * Coefficient;
	VelocityMax[Polar] = VelocityMax[Cartographic] * Coefficient;

	// Current
	Acceleration[Current] = Acceleration[Cartographic];
	Deceleration[Current] = Deceleration[Cartographic];
	VelocityMax[Current] = VelocityMax[Cartographic];
}

MovementComponent::~MovementComponent()
{
	//
}


// Functions:

void MovementComponent::Move(const float dirX, const float dirY, const float& dt)
{
	// X
	Velocity.x += Acceleration[Current] * dirX * dt;

	// Y
	Velocity.y += Acceleration[Current] * dirY * dt;
}

const bool MovementComponent::CheckStatus(MovementStatus status) const
{
	switch (status)
	{
		case MovementStatus::Idle:
		{
			if (Velocity.x == 0.f && Velocity.y == 0.f)
			{
				return true;

				break;
			}
		}

		case MovementStatus::Moving:
		{
			if (Velocity.x != 0.f && Velocity.y != 0.f)
			{
				return true;

				break;
			}
		}
	}

	return false;
}

void MovementComponent::Update(const float& dt)
{
	if (Velocity.x != 0.f && Velocity.y != 0.f)
	{
		Acceleration[Current] = Acceleration[Polar];
		Deceleration[Current] = Deceleration[Polar];
		VelocityMax[Current] = VelocityMax[Polar];
	}
	else
	{
		Acceleration[Current] = Acceleration[Cartographic];
		Deceleration[Current] = Deceleration[Cartographic];
		VelocityMax[Current] = VelocityMax[Cartographic];
	}

	// X:
	if (Velocity.x > 0.f) //Check for right
	{
		//Max Velocity check positive
		if (Velocity.x > VelocityMax[Current])
		{
			Velocity.x = VelocityMax[Current];
		}

		//Deceleration positive
		Velocity.x -= Deceleration[Current] * dt;

		if (Velocity.x < 0.f)
		{
			Velocity.x = 0.f;
		}
	}
	else if (Velocity.x < 0.f) //Check for left
	{
		//Max Velocity check negative
		if (Velocity.x < -VelocityMax[Current])
		{
			Velocity.x = -VelocityMax[Current];
		}

		//Deceleration negative
		Velocity.x += Deceleration[Current] * dt;

		if (Velocity.x > 0.f)
		{
			Velocity.x = 0.f;
		}
	}

	// Y:
	if (Velocity.y > 0.f) //Check for Down
	{
		//Max Velocity check positive
		if (Velocity.y > VelocityMax[Current])
		{
			Velocity.y = VelocityMax[Current];
		}

		//Deceleration positive
		Velocity.y -= Deceleration[Current] * dt;

		if (Velocity.y < 0.f)
		{
			Velocity.y = 0.f;
		}
	}
	else if (Velocity.y < 0.f) //Check for Up
	{
		//Max Velocity check negative
		if (Velocity.y < -VelocityMax[Current])
		{
			Velocity.y = -VelocityMax[Current];
		}

		//Deceleration negative
		Velocity.y += Deceleration[Current] * dt;

		if (Velocity.y > 0.f)
		{
			Velocity.y = 0.f;
		}
	}

	// Final move
	EntitySprite.move(Velocity * dt);
}


// Accessors:

const float& MovementComponent::GetVelocityMax() const
{
	return VelocityMax[Current];
}

const sf::Vector2f& MovementComponent::GetVelocity() const
{
	return Velocity;
}


// Private Functions:

void MovementComponent::InitVariables()
{
	//
}
