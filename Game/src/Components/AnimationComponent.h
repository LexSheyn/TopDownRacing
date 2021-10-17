#pragma once

#include "Base/Component.h"
#include "../Animation/Animation.h"

class AnimationComponent : public Component
{
public:

// Constructors and Destructor:

	AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet);

	~AnimationComponent();

// Functions:

	void AddAnimation
	(
		const int32& index, const float animationTimer,
		const int32 firstFrameX, const int32 firstFrameY,
		const int32 lastFrameX, const int32 lastFrameY,
		const int32 width, const int32 height
	);

	const bool& Play(const int32& index, const float& dt, const bool prioritized = false);
	const bool& Play(const int32& index, const float& modifier, const float& modifierMax, const float& dt, const bool prioritized = false);

// Accessors:

	const bool& IsFinished(const int32& index) const;

private:

// Private Functions:

	void InitVariables();

// Variables:

	sf::Sprite& Sprite;
	sf::Texture& TextureSheet;
	std::map<int32, Animation*> Animations;
	Animation* AnimationLast;
	Animation* AnimationPrioritized;
};

