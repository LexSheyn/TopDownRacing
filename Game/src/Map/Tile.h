#pragma once

#include "../Entities/Player.h"

class Tile
{
public:

// Constructors and Destructor:

	// Use grid size.
	Tile
	(
		const int32 x, const int32 y, const float gridSize, 
		const sf::Texture& texture, const sf::IntRect& textureRect, 
		const bool collision
	);

	~Tile();

// Functions:

	const bool Intersects(const sf::FloatRect bounds) const;

	const std::string GetAsString() const;

	void Update(const float& dt);

	void Render(sf::RenderTarget* target, const bool showCollision = false);

// Accessors:

	const bool& GetCollision() const;

	const sf::Vector2f GetPosition() const;

	const sf::Vector2f GetCenter() const;

	const sf::FloatRect GetGlobalBounds() const;

	const float GetDistance(const Tile* tile) const;
	const float GetDistance(const Entity* entity) const;

	Collider& GetCollider() const;

private:

// Variables:

	sf::Sprite TileSprite;
	sf::RectangleShape CollisionBox;
	bool Collision;

	Collider* TileCollider;
};

