#include "../stdafx.h"
#include "AnimationComponent.h"

// Constructors and Destructor:

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet)
	: EntitySprite(sprite), TextureSheet(textureSheet)
{
	InitVariables();
}

AnimationComponent::~AnimationComponent()
{
}


// Functions:

void AnimationComponent::AddAnimation(const std::string& name, const float time, const int32 firstFrameX, const int32 firstFrameY, const int32 lastFrameX, const int32 lastFrameY, const int32 width, const int32 height)
{
}

const bool& AnimationComponent::Play(const std::string& name, const float& dt, const bool prioritized)
{
	// TODO: insert return statement here
	// TEST
	static bool a = false;
	return a;
}

const bool& AnimationComponent::Play(const std::string& name, const float& modifier, const float& modifierMax, const float& dt, const bool prioritized)
{
	// TODO: insert return statement here
	// TEST
	static bool b = false;
	return b;
}


// Accessors:

const bool& AnimationComponent::IsComplete(const std::string& name) const
{
	// TODO: insert return statement here
	// TEST
	static bool c = false;
	return c;
}


// Private Functions:

void AnimationComponent::InitVariables()
{
	AnimationLast = nullptr;
	
	AnimationPrioritized = nullptr;
}
