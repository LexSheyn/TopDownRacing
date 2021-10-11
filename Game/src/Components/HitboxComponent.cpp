#include "../stdafx.h"
#include "HitboxComponent.h"

// Constructors and Destructor:

HitboxComponent::HitboxComponent(sf::Sprite& sprite, const float width, const float height)
	: EntitySprite(sprite)
{
	NextPosition.left = 0.f;
	NextPosition.top = 0.f;
	NextPosition.width = width;
	NextPosition.height = height;

	Hitbox.setSize(sf::Vector2f(width, height));
	Hitbox.setOrigin(Hitbox.getSize() / 2.f);
	Hitbox.setPosition(EntitySprite.getPosition());
	Hitbox.setFillColor(sf::Color::Transparent);
	Hitbox.setOutlineThickness(-1.f);
	Hitbox.setOutlineColor(sf::Color::Green);
}

HitboxComponent::~HitboxComponent()
{
}


// Functions:

bool HitboxComponent::Intersects(const sf::FloatRect& rect)
{
	return Hitbox.getGlobalBounds().intersects(rect);
}

void HitboxComponent::Update()
{
//	Hitbox.setPosition(EntitySprite.getPosition());
	EntitySprite.setPosition(Hitbox.getPosition());
}

void HitboxComponent::Render(sf::RenderTarget* target, const bool visible)
{
	if (visible)
	{
		target->draw(Hitbox);
	}
}


// Accessors:

sf::RectangleShape& HitboxComponent::GetHitbox()
{
	return Hitbox;
}

const sf::Vector2f HitboxComponent::GetPosition() const
{
	return Hitbox.getPosition();
}

const sf::FloatRect HitboxComponent::GetGlobalBounds() const
{
	return Hitbox.getGlobalBounds();
}

const sf::FloatRect& HitboxComponent::GetNextPosition(const sf::Vector2f& velocity)
{
	NextPosition.left = Hitbox.getPosition().x + velocity.x;
	NextPosition.top = Hitbox.getPosition().y + velocity.y;

	return NextPosition;
}


// Modifiers:

void HitboxComponent::SetPosition(const float x, const float y)
{
	Hitbox.setPosition(x, y);

	EntitySprite.setPosition(x, y);
}
