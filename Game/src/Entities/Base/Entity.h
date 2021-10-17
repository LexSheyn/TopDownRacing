#pragma once

#include "../../Components/MovementComponent.h"
#include "../../Components/EngineComponent.h"
#include "../../Components/HitboxComponent.h"
#include "../../Components/AnimationComponent.h"
#include "../../Components/AttributeComponent.h"
#include "../../Systems/Collider.h"

class Entity
{
public:

// Constructors and Destructor:

	Entity();

	virtual ~Entity();

// Functions:

	void Move(const float dirX, const float dirY, const float& dt);

	void Drive(const float& dt);

	void Reverse(const float& dt);

	void TurnLeft(const float& dt);

	void TurnRight(const float& dt);

	void InvertVelocity();
	
	void InvertVelocityX();
	
	void InvertVelocityY();

	// Pure virtual
	virtual void Update(const float& dt, sf::Vector2f& mousePositioView) = 0;

	// Pure virtual
	virtual void Render(sf::RenderTarget* target, const bool showHitbox) = 0;

// Accessors:

	const sf::Vector2f GetPosition() const;

	const sf::Vector2i GetPositionGrid(const int32 gridSizeI) const;

	const sf::FloatRect GetGlobalBounds() const;

	const sf::FloatRect GetNextPositionBounds(const float& dt) const;

	EngineComponent* GetEngineComponent() const;

	const AttributeComponent* GetAttributeComponent() const;

	const float GetDistance(const Entity* entity) const;

	const bool IsDead() const;

// Modifiers:

	void SetTexture(sf::Texture& texture);

	void SetOriginToCenter();

	void SetPosition(const float x, const float y);

	void SetPositionGrid(const int32 gridSize, const int32 x, const int32 y);

	void GainHp(const int32 hp);

	void LoseHp(const int32 hp);

// Component Functions:

	void CreateHitboxComponent(const float width, const float height);

	void CreateMovementComponent(const float velocityMax, const float acceleration, const float deceleration);

	void CreateEngineComponent(HitboxComponent* hitbox, const float speedMax, const float boostMax, const float deceleration);	

	void CreateAnimationComponent(sf::Texture& textureSheet);

	void CreateAttributeComponent(const int32 hpMax);

protected:

	sf::Sprite Sprite;

	// Components
	HitboxComponent* Hitbox;
	MovementComponent* Movement;
	EngineComponent* Engine;	
	AnimationComponent* Animations;
	AttributeComponent* Attributes;

private:

// Private Functions:

	void InitVariables();
};

