#pragma once

#include "Base/Menu.h"

class PauseMenu : public Menu
{
public:

	// Constructors and Destructor:

	PauseMenu(sf::VideoMode& videoMode, sf::Font& font);

	~PauseMenu();

	// Functions:

		// Positions available from top to bottom: 0 - 7.
	void AddButton(const uint32 index, const uint32 position, sf::Texture* texture);

	void ResetGui() override;

	void Update(const sf::Vector2i& mousePosition, const float& dt) override;

	void Render(sf::RenderTarget* target) override;

private:

	// Private Functions:

	void InitVariables();

	void InitGui();

	// Variables:

	Logger Log;

	static const uint32 ButtonsAmount = 8u;

	gui::Button* ButtonPtr[ButtonsAmount];
	uint32 ButtonPtrSize;

	uint32 ButtonIndex[ButtonsAmount];
	uint32 ButtonIndexSize;

	sf::Texture* ButtonTexture[ButtonsAmount];
	uint32 ButtonTextureSize;

	sf::VideoMode& VideoMode;
};