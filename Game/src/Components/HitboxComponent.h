#pragma once

#include "Base/Component.h"

class HitboxComponent : public Component
{
public:

// Constructors and Destructor:

	HitboxComponent(sf::Sprite& sprite, const float width, const float height);

	~HitboxComponent();

// Functions:

	bool Intersects(const sf::FloatRect& rect);

	void Update();

	void Render(sf::RenderTarget* target, const bool visible);

// Accessors:

	sf::RectangleShape& GetHitbox();

	const sf::Vector2f GetPosition() const;

	const sf::FloatRect GetGlobalBounds() const;

	const sf::FloatRect& GetNextPosition(const sf::Vector2f& velocity);

// Modifiers:

	void SetPosition(const float x, const float y);

private:

// Variables:

	sf::Sprite& Sprite;
	sf::RectangleShape Hitbox;
	sf::FloatRect NextPosition;
};

