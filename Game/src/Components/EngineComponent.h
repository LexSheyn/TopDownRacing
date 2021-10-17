#pragma once

#include "Base/Component.h"

class EngineComponent : public Component
{
public:

// Statuses

	enum class Status : int32
	{
		Idle = 0, Driving
	};

// Concstructors and Destructor:

	EngineComponent(sf::Sprite& sprite, sf::RectangleShape& hitbox, const float speedMax, const float boostMax, const float deceleration);

	~EngineComponent();

// Functions:

	void Drive(const float& dt);

	void Reverse(const float& dt);

	void TurnLeft(const float& dt);

	void TurnRight(const float& dt);

	void InvertVelocity();

	void InvertVelocityX();

	void InvertVelocityY();

	const bool CheckStatus(Status status) const;

	void Update(const float& dt);

// Accessors:

	const float& GetBoost() const;

	const float& GetSpeedMax() const;

	const sf::Vector2f& GetVelocity() const;

	const sf::Vector2f& GetVelocityMax() const;

	const float GetVelocityLength() const;

	const float GetVelocityLengthMax();

private:

// Private Functions:

	void InitVariables();

// Variables:

	sf::Sprite& Sprite;

	sf::RectangleShape& Hitbox;

	sf::Vector2f Acceleration;

	float Deceleration;

	float SpeedMax;

	float BoostMax;

	float Boost;

	sf::Vector2f Velocity;

	float Angle;

	const float Pi;
};
