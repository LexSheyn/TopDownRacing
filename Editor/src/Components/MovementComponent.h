#pragma once

#include "Base/Component.h"

enum class MovementStatus : int32
{
	Idle = 0, Moving
};

class MovementComponent : public Component
{
public:

// Constructors and Destructor:

	MovementComponent(sf::Sprite& sprite, const float velocityMax, const float acceleration, const float deceleration);

	~MovementComponent();

// Functions:	

	void Move(const float dirX, const float dirY, const float& dt);

	const bool CheckStatus(MovementStatus status) const;

	void Update(const float& dt);

// Accessors:

	const float& GetVelocityMax() const;

	const sf::Vector2f& GetVelocity() const;

private:

// Private Functions:

	void InitVariables();

// Variables:

	enum VelocityTypes : uint32
	{
		Current = 0, Cartographic, Polar
	};

	sf::Sprite& EntitySprite;
	
	float Acceleration[3];

	float Deceleration[3];

	float VelocityMax[3];

	sf::Vector2f Velocity;

	const float Pi;
	
	const float Coefficient;
};

