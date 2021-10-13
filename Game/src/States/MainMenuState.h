#pragma once

#include "GameState.h"

class MainMenuState : public State
{
public:

// Constructors and Destructor:

	MainMenuState(StateData* stateData);

	~MainMenuState();

// Functions:

	void ResetGui() override;

	void UpdateInput(const float& dt) override;

	void UpdateButtons(const float& dt);

	void Update(const float& dt) override;

	void RenderButtons(sf::RenderTarget* target);

	void Render(sf::RenderTarget* target) override;

private:

// Private Functions:

	void InitVariables();

	void InitBackground(const std::string& filePath);

	void InitGui();

	void InitSound() override;

// Variables:

	// Logger
	Logger Log;

	// Core
	sf::Texture BackgroundTexture;
	sf::RectangleShape Background;
	sf::RectangleShape Container;

	// Buttons
	enum ButtonName : int32
	{
		Start = 0, Settings, Exit
	};

//	gui::DropDownList List;

	std::map<const ButtonName, gui::Button*> Buttons;
	std::map<const ButtonName, sf::Texture> ButtonTextures;
};

