#pragma once

#include "../../Graphics/GraphicsSettings.h"
#include "../../GUI/Resizers.h"
#include "../../GUI/Button.h"

class StateData;

class State
{
public:

// Constructors and Destructor:

	// To do...
	State(StateData* stateData);

	virtual ~State();

// Functions:

	void EndState();
	
	void PauseState();

	void UnpauseState();

	void UpdateMousePositions(sf::View* view = nullptr);

	void UpdateSound(const float& dt);

	void UpdteMousePositionText();

	void UpdateFpsCounter(const float& dt);

	// Pure virtual
	virtual void UpdateInput(const float& dt) = 0;

	// Pure virtual
	virtual void Update(const float& dt) = 0;

	void RenderMousePositionText(sf::RenderTarget* target);

	void RenderFpsCounter(sf::RenderTarget* target);

	// Pure virtual
	virtual void Render(sf::RenderTarget* target) = 0;

// Accessors:

	const bool& IsPaused() const;

	const bool& IsEnded() const;

	const bool GetKeyTime();
	const bool GetKeyTime(const float& keyTimeMax);

protected:

// Protected Functions:

	bool InitKeybinds(const std::string& filePath);

	bool InitFont(sf::Font& font, const std::string& filePath);

	bool InitTexture(sf::Texture& texture, const std::string& filePath);

	// Pure virtual
	virtual void InitSound() = 0;

	void InitKeyTime();

	void InitMousePositionText();

	void InitFpsCounter();

// Variables:

	// Logger
	Logger StateLog;

	// Core
	StateData* StData;

	float GridSize;

	sf::RenderWindow* Window;

	std::map<const std::string, int32>* SupportedKeys;

	std::map<const std::string, int32> Keybinds;

	sfx::SoundEngine* SoundEngine;

	std::stack<State*>* States;

	bool Ended;

	bool Paused;

	float KeyTimeMax;

	sf::Clock KeyTimer;	

	// Mouse positions
	sf::Vector2i MousePositionScreen;
	sf::Vector2i MousePositionWindow;
	sf::Vector2f MousePositionView;
	sf::Vector2i MousePositionGrid;

	// Randimizer
//	Randomizer Randomizer;

	// Font and text
	sf::Font Font;
	sf::Text MousePositionTextX;
	sf::Text MousePositionTextY;
	sf::Text FpsCounterText;

	// Textures
//	std::map<const int32, sf::Texture> PlayerTexture;
	std::map<const int32, sf::Texture> ButtonTextures;
	sf::Texture PlayerTexture;
};

class StateData
{
public:

	// Variables:

	float GridSize;

	sf::RenderWindow* Window;

	GraphicsSettings* GfxSettings;

	std::map<const std::string, int32>* SupportedKeys;

	sfx::SoundEngine* SoundEngine;

	std::stack<State*>* States;
};
