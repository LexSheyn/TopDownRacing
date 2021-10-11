#include "../stdafx.h"
#include "Tile.h"

// Constructors and Destructor:

Tile::Tile(const int32 x, const int32 y, const float gridSize, const sf::Texture& texture, const sf::IntRect& textureRect, const bool collision)
{
	TileSprite.setPosition
	(
		static_cast<float>(x) * gridSize,
		static_cast<float>(y) * gridSize
	);

	TileSprite.setTexture(texture);

	TileSprite.setTextureRect(textureRect);

	CollisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	CollisionBox.setOrigin(CollisionBox.getSize() / 2.f);
	CollisionBox.setPosition(TileSprite.getPosition() + CollisionBox.getSize() / 2.f);
	CollisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	CollisionBox.setOutlineColor(sf::Color::Red);
	CollisionBox.setOutlineThickness(-1.f);	

	Collision = collision;

	TileCollider = new Collider(CollisionBox);
}

Tile::~Tile()
{

}


// Functions:

const bool Tile::Intersects(const sf::FloatRect bounds) const
{
	return TileSprite.getGlobalBounds().intersects(bounds);
}

const std::string Tile::GetAsString() const
{
	std::stringstream ss;

	ss << TileSprite.getTextureRect().left << " " << TileSprite.getTextureRect().top << " " << Collision;

	return ss.str();
}

void Tile::Update(const float& dt)
{
	//
}

void Tile::Render(sf::RenderTarget* target, const bool showCollision)
{
	target->draw(TileSprite);

	if (Collision && showCollision)
	{
		target->draw(CollisionBox);
	}
}


// Accessors:

const bool& Tile::GetCollision() const
{
	return Collision;
}

const sf::Vector2f Tile::GetPosition() const
{
	if (Collision)
	{
		return CollisionBox.getPosition();
	}

	return TileSprite.getPosition();
}

const sf::Vector2f Tile::GetCenter() const
{
	if (Collision)
	{
		return CollisionBox.getPosition();
	}

	return sf::Vector2f
	(
		TileSprite.getPosition().x + TileSprite.getGlobalBounds().width / 2.f,
		TileSprite.getPosition().y + TileSprite.getGlobalBounds().height / 2.f
	);
}

const sf::FloatRect Tile::GetGlobalBounds() const
{
	if (Collision)
	{
		return CollisionBox.getGlobalBounds();
	}

	return TileSprite.getGlobalBounds();
}

const float Tile::GetDistance(const Tile* tile) const
{
	return static_cast<float>(std::sqrt(std::pow((GetCenter().x - tile->GetCenter().x), 2) + std::pow((GetCenter().y - tile->GetCenter().y), 2)));
}

const float Tile::GetDistance(const Entity* entity) const
{
	return static_cast<float>(std::sqrt(std::pow((GetCenter().x - entity->GetPosition().x), 2) + std::pow((GetCenter().y - entity->GetPosition().y), 2)));
}

Collider& Tile::GetCollider()
{
	return *TileCollider;
}
