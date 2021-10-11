#pragma once

#include "Base/Component.h"

enum class EngineStatus : int32
{
	Idle = 0, Driving
};

class EngineComponent : public Component
{
public:

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

	const bool CheckStatus(EngineStatus status) const;

	void Update(const float& dt);

// Accessors:

	const float& GetBoost() const;

	const float& GetSpeedMax() const;

	const sf::Vector2f& GetVelocity() const;

private:

// Private Functions:

	void InitVariables();

// Variables:

	sf::Sprite& EntitySprite;

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
