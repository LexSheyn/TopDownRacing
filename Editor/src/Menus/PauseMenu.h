#pragma once

#include "Base/Menu.h"

class PauseMenu : public Menu
{
public:

// Constructors and Destructor:

	PauseMenu(sf::VideoMode videoMode, sf::Font& font);

	~PauseMenu();

// Functions:

	void Update(const sf::Vector2i& mousePosition, const float& dt) override;

	void Render(sf::RenderTarget* target) override;
};