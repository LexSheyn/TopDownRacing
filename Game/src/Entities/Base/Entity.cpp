#include "../../stdafx.h"
#include "Entity.h"

// Constructors and Destructor:

Entity::Entity()
{
	InitVariables();
}

Entity::~Entity()
{
	// Deleting components
	delete Hitbox;
	delete Movement;
	delete Engine;	
	delete Animations;
	delete Attributes;
}


// Functions:

void Entity::Move(const float dirX, const float dirY, const float& dt)
{
	if (Movement)
	{
		Movement->Move(dirX, dirY, dt);
	}
}

void Entity::Drive(const float& dt)
{
	if (Engine)
	{
		Engine->Drive(dt);
	}
}

void Entity::Reverse(const float& dt)
{
	if (Engine)
	{
		Engine->Reverse(dt);
	}
}

void Entity::TurnLeft(const float& dt)
{
	if (Engine)
	{
		Engine->TurnLeft(dt);
	}
}

void Entity::TurnRight(const float& dt)
{
	if (Engine)
	{
		Engine->TurnRight(dt);
	}
}

void Entity::InvertVelocity()
{
	if (Engine)
	{
		Engine->InvertVelocity();
	}
}

void Entity::InvertVelocityX()
{
	if (Engine)
	{
		Engine->InvertVelocityX();
	}
}

void Entity::InvertVelocityY()
{
	if (Engine)
	{
		Engine->InvertVelocityY();
	}
}


// Accessors:

const sf::Vector2f Entity::GetPosition() const
{
	if (Hitbox)
	{
		return Hitbox->GetPosition();
	}

	return Sprite.getPosition();
}

const sf::Vector2i Entity::GetPositionGrid(const int32 gridSizeI) const
{
	if (Hitbox)
	{
		return sf::Vector2i
		(
			static_cast<int32>(Hitbox->GetPosition().x / gridSizeI),
			static_cast<int32>(Hitbox->GetPosition().y / gridSizeI)
		);
	}

	return sf::Vector2i
	(
		static_cast<int32>(Sprite.getPosition().x / gridSizeI),
		static_cast<int32>(Sprite.getPosition().y / gridSizeI)
	);
}

const sf::FloatRect Entity::GetGlobalBounds() const
{
	if (Hitbox)
	{
		return Hitbox->GetGlobalBounds();
	}

	return Sprite.getGlobalBounds();
}

const sf::FloatRect Entity::GetNextPositionBounds(const float& dt) const
{
	if (Movement && Hitbox)
	{
		return Hitbox->GetNextPosition(Movement->GetVelocity() * dt);
	}
	else if (Engine && Hitbox)
	{
		return Hitbox->GetNextPosition(Engine->GetVelocity() * dt);
	}

	// Error
	return sf::FloatRect();
}

const EngineComponent* Entity::GetEngineComponent() const
{
	return Engine;
}

const AttributeComponent* Entity::GetAttributeComponent() const
{
	return Attributes;
}

const float Entity::GetDistance(const Entity* entity) const
{
	return static_cast<float>(std::sqrt(std::pow((GetPosition().x - entity->GetPosition().x), 2) + std::pow((GetPosition().y - entity->GetPosition().y), 2)));
}

const bool Entity::IsDead() const
{
	if (Attributes)
	{
		return Attributes->IsDead();
	}

	return false;
}


// Modifiers:

void Entity::SetTexture(sf::Texture& texture)
{
	Sprite.setTexture(texture);	
}

void Entity::SetOriginToCenter()
{
	Sprite.setOrigin(Sprite.getPosition() + sf::Vector2f(Sprite.getGlobalBounds().width / 2.f, Sprite.getGlobalBounds().height / 2.f));
}

void Entity::SetPosition(const float x, const float y)
{
	if (Hitbox)
	{
		Hitbox->SetPosition(x, y);
	}
	else
	{
		Sprite.setPosition(x, y);
	}
}

void Entity::SetPositionGrid(const int32 gridSize, const int32 x, const int32 y)
{
	// To do...
}

void Entity::GainHp(const int32 hp)
{
	if (Attributes)
	{
		Attributes->GainHp(hp);
	}
}

void Entity::LoseHp(const int32 hp)
{
	if (Attributes)
	{
		Attributes->LoseHp(hp);
	}
}


// Component Functions:

void Entity::CreateHitboxComponent(const float width, const float height)
{
	Hitbox = new HitboxComponent(Sprite, width, height);
}

void Entity::CreateMovementComponent(const float velocityMax, const float acceleration, const float deceleration)
{
	Movement = new MovementComponent(Sprite, velocityMax, acceleration, deceleration);
}

void Entity::CreateEngineComponent(HitboxComponent* hitbox, const float speedMax, const float boostMax, const float deceleration)
{
	Engine = new EngineComponent(Sprite, hitbox->GetHitbox(), speedMax, boostMax, deceleration);
}

void Entity::CreateAnimationComponent(sf::Texture& textureSheet)
{
	Animations = new AnimationComponent(Sprite, textureSheet);
}

void Entity::CreateAttributeComponent(const int32 hpMax)
{
	Attributes = new AttributeComponent(hpMax);
}


// Private Functions:

void Entity::InitVariables()
{
	Movement = nullptr;
	Engine = nullptr;
	Hitbox = nullptr;
	Animations = nullptr;
	Attributes = nullptr;
}
