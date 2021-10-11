#include "../stdafx.h"
#include "Player.h"

// Constructors and Destructor:

Player::Player(sf::Texture& texture, const float x, const float y)
{
	InitVariables();

	Entity::SetTexture(texture);

	Entity::SetOriginToCenter();

	// Components initialization
	Entity::CreateHitboxComponent(48.f, 48.f);

	Entity::CreateEngineComponent(Hitbox, 500.f, 600.f, 200.f);	

	Entity::CreateAttributeComponent(100);

	Entity::SetPosition(x, y);

	InitAnimations();

	PlayerCollider = new Collider(Hitbox->GetHitbox());
}

Player::~Player()
{
	//
}


// Functions:

void Player::PlayAnimation()
{
}

void Player::UpdateAnimations(const float& dt)
{
	//
}

void Player::Update(const float& dt, sf::Vector2f& mousePositionView)
{
//	Movement->Update(dt);

	Engine->Update(dt);

	Hitbox->Update();

	UpdateAnimations(dt);
}

void Player::Render(sf::RenderTarget* target, const bool showHitbox)
{
	target->draw(EntitySprite);

	if (showHitbox)
	{
		Hitbox->Render(target, showHitbox);
	}
}


// Accessors:

const float Player::GetRotation() const
{
	return EntitySprite.getRotation();
}

Collider& Player::GetCollider()
{
	return *PlayerCollider;
}


// Private Functions:

void Player::InitVariables()
{
	//
}

void Player::InitAnimations()
{
	//
}
