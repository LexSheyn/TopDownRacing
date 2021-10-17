#include "../stdafx.h"
#include "Animation.h"

// Constructors and Destructor:

Animation::Animation
(
	sf::Sprite& sprite, sf::Texture& textureSheet, 
	const float animationTimer, 
	int32 firstFrameX, int32 firstFrameY, int32 lastFrameX, int32 lastFrameY, 
	int32 width, int32 height
) : Sprite(sprite), TextureSheet(textureSheet), AnimationTimer(animationTimer), Timer(animationTimer),
	Finished(false), Width(width), Height(height)
{
	StartRect = sf::IntRect(firstFrameX * width, firstFrameY * height, width, height);
	CurrentRect = StartRect;
	EndRect = sf::IntRect(lastFrameX * width, lastFrameY * height, width, height);

	Sprite.setTexture(TextureSheet, true);
	Sprite.setTextureRect(StartRect);
}

Animation::~Animation()
{
}


// Functions:

const bool& Animation::Play(const float& dt)
{
	Finished = false;

	Timer += 100.f * dt;

	if (Timer >= AnimationTimer)
	{
		Timer = 0.f;

		if (CurrentRect != EndRect)
		{
			CurrentRect.left += Width;
		}
		else
		{
			CurrentRect.left = StartRect.left;

			Finished = true;
		}

		Sprite.setTextureRect(CurrentRect);
	}

	return Finished;
}

const bool& Animation::Play(float modifier, const float& dt)
{
	if (modifier < 0.f)
	{
		modifier = 0.f;
	}

	Finished = false;

	Timer += modifier * 100.f * dt;

	if (Timer >= AnimationTimer)
	{
		Timer = 0.f;

		if (CurrentRect != EndRect)
		{
			CurrentRect.left += Width;
		}
		else
		{
			CurrentRect.left = StartRect.left;

			Finished = true;
		}

		Sprite.setTextureRect(CurrentRect);
	}

	return Finished;
}

void Animation::Reset()
{
	Timer = AnimationTimer;

	CurrentRect = StartRect;
}


// Accessors:

const bool& Animation::IsFinished() const
{
	return Finished;
}
