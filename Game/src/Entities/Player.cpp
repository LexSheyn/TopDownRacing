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

	Entity::CreateAnimationComponent(texture);

	Entity::SetPosition(x, y);

	InitAnimations();

	PlayerCollider = new Collider(Hitbox->GetHitbox());
}

Player::~Player()
{
	//
}


// Functions:

void Player::PlayAnimation(const int32& index, const float& dt, const bool priority)
{
	Animations->Play(index, dt, priority);
}

void Player::UpdateAnimations(const float& dt)
{
	//
}

void Player::Update(const float& dt, sf::Vector2f& mousePositionView)
{
	Engine->Update(dt);

	Hitbox->Update();

	UpdateAnimations(dt);
}

void Player::Render(sf::RenderTarget* target, const bool showHitbox)
{
	target->draw(Sprite);

	if (showHitbox)
	{
		Hitbox->Render(target, showHitbox);
	}
}


// Accessors:

const float Player::GetRotation() const
{
	return Sprite.getRotation();
}

Collider& Player::GetCollider() const
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
	Animations->AddAnimation(IDLE,    10.f, 00, 00, 05, 00, 64.f, 64.f);
	Animations->AddAnimation(DRIVING, 10.f, 00, 01, 05, 01, 64.f, 64.f);
}
