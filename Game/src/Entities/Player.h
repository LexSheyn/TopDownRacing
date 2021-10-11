#pragma once

#include "Base/Entity.h"

class Player : public Entity
{
public:

// Constructors and Destructor:

	Player(sf::Texture& texture, const float x, const float y);

	~Player();

// Functions:

	void PlayAnimation(); // To do...

	void UpdateAnimations(const float& dt);

	void Update(const float& dt, sf::Vector2f& mousePositionView) override;

	void Render(sf::RenderTarget* target, const bool showHitbox) override;

// Accessors:

	const float GetRotation() const;

	Collider& GetCollider() const;

private:

// Private Functions:

	void InitVariables();

	void InitAnimations();

// Variables:

	Collider* PlayerCollider;
};

