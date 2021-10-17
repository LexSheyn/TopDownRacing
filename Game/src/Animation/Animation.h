#pragma once
class Animation
{
public:

// Constructors and Destructor:

	Animation
	(
		sf::Sprite& sprite, sf::Texture& textureSheet,
		const float animationTimer,
		int32 firstFrameX, int32 firstFrameY, int32 lastFrameX, int32 lastFrameY,
		int32 width, int32 height
	);

	~Animation();

// Functions:

	const bool& Play(const float& dt);
	const bool& Play(float modifier, const float& dt);

	void Reset();

// Accessors:

	const bool& IsFinished() const;

// Variables:

	sf::Sprite& Sprite;
	sf::Texture& TextureSheet;
	float AnimationTimer;
	float Timer;
	bool Finished;
	int32 Width;
	int32 Height;
	sf::IntRect StartRect;
	sf::IntRect CurrentRect;
	sf::IntRect EndRect;
};

