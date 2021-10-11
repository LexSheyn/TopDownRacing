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
		const std::string& name, const float time,
		const int32 firstFrameX, const int32 firstFrameY,
		const int32 lastFrameX, const int32 lastFrameY,
		const int32 width, const int32 height
	);

	const bool& Play(const std::string& name, const float& dt, const bool prioritized = false);
	const bool& Play(const std::string& name, const float& modifier, const float& modifierMax, const float& dt, const bool prioritized = false);

// Accessors:

	const bool& IsComplete(const std::string& name) const;

private:

// Private Functions:

	void InitVariables();

// Variables:

	sf::Sprite& EntitySprite;
	sf::Texture& TextureSheet;
	std::map<const std::string, Animation*> Animations;
	Animation* AnimationLast;
	Animation* AnimationPrioritized;
};

