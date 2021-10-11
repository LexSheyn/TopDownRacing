#pragma once

class Collider
{
public:

// Constructors and Destructor:

	Collider(sf::RectangleShape& body);

	~Collider();

// Functions:

	void Move(const float dx, const float dy);

	// No collision = 0.
	// X = 1.
	// Y = 2.	
	int32 CheckCollision(Collider& other, float push);

// Accessors:

	sf::Vector2f GetPosition();

	sf::Vector2f GetHalfSize();

private:

// Variables:

	sf::RectangleShape& Body;

	int32 Result;

	sf::Vector2f OtherPosition;
	sf::Vector2f OtherHalfSize;
	
	sf::Vector2f ThisPosition;
	sf::Vector2f ThisHalfSize;

	float DeltaX;
	float DeltaY;

	float IntersectX;
	float IntersectY;
};