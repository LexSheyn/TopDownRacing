#include "../stdafx.h"
#include "AnimationComponent.h"

// Constructors and Destructor:

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet)
	: Sprite(sprite), TextureSheet(textureSheet)
{
	InitVariables();
}

AnimationComponent::~AnimationComponent()
{
	// Deleting animations
	for (auto& animation : Animations)
	{
		delete animation.second;
	}

	Animations.clear();
}


// Functions:

void AnimationComponent::AddAnimation(const int32& index, const float animationTimer, const int32 firstFrameX, const int32 firstFrameY, const int32 lastFrameX, const int32 lastFrameY, const int32 width, const int32 height)
{
	Animations[index] = new Animation
	(
		Sprite, TextureSheet,
		animationTimer,
		firstFrameX, firstFrameY, lastFrameX, lastFrameY, width, height
	);
}

const bool& AnimationComponent::Play(const int32& index, const float& dt, const bool prioritized)
{
	//If there is a priority animation
	if (AnimationPrioritized)
	{
		if (AnimationPrioritized == Animations[index])
		{
			if (AnimationLast != Animations[index])
			{
				if (AnimationLast == nullptr)
				{
					AnimationLast = Animations[index];
				}
				else
				{
					AnimationLast->Reset();

					AnimationLast = Animations[index];
				}
			}

			//If the priority animation is done - remove it
			if (Animations[index]->Play(dt))
			{
				AnimationPrioritized = nullptr;
			}
		}
	}
	else //Play animation if no other priority animation is set
	{
		//If priprity is true - set this animation to priority
		if (prioritized)
		{
			AnimationPrioritized = Animations[index];
		}

		if (AnimationLast != Animations[index])
		{
			if (AnimationLast == nullptr)
			{
				AnimationLast = Animations[index];
			}
			else
			{
				AnimationLast->Reset();

				AnimationLast = Animations[index];
			}
		}

		Animations[index]->Play(dt);
	}

	return Animations[index]->IsFinished();
}

const bool& AnimationComponent::Play(const int32& index, const float& modifier, const float& modifierMax, const float& dt, const bool prioritized)
{
	//If there is a priority animation
	if (AnimationPrioritized)
	{
		if (AnimationPrioritized == Animations[index])
		{
			if (AnimationLast != Animations[index])
			{
				if (AnimationLast == nullptr)
				{
					AnimationLast = Animations[index];
				}
				else
				{
					AnimationLast->Reset();

					AnimationLast = Animations[index];
				}
			}

			//If the priority animation is done - remove it
			if (Animations[index]->Play(dt))
			{
				AnimationPrioritized = nullptr;
			}
		}
	}
	else //Play animation if no other priority animation is set
	{
		//If priprity is true - set this animation to priority
		if (prioritized)
		{
			AnimationPrioritized = Animations[index];
		}

		if (AnimationLast != Animations[index])
		{
			if (AnimationLast == nullptr)
			{
				AnimationLast = Animations[index];
			}
			else
			{
				AnimationLast->Reset();

				AnimationLast = Animations[index];
			}
		}

		Animations[index]->Play(std::abs(modifier / modifierMax), dt);
	}

	return Animations[index]->IsFinished();
}


// Accessors:

const bool& AnimationComponent::IsFinished(const int32& index) const
{
	return Animations.at(index)->IsFinished();
}


// Private Functions:

void AnimationComponent::InitVariables()
{
	AnimationLast = nullptr;
	
	AnimationPrioritized = nullptr;
}
