#pragma once

#include "../../GUI/DropDownList.h"

class Menu
{
public:

// Constructors and Destructor:

	Menu(sf::VideoMode& videoMode, sf::Font& font);

	virtual ~Menu();

// Functions:
	
	// Pure virtual
	virtual void ResetGui() = 0;

	// Pure virtual
	virtual void Update(const sf::Vector2i& mousePosition, const float& dt) = 0;
	
	// Pure virtual
	virtual void Render(sf::RenderTarget* target) = 0;

// Accessors:

	const bool IsButtonPressed(const uint32 index);

protected:

// Protected Functions:

	void InitTexture(sf::Texture& texture, const std::string& filePath);

// Variables:

	sf::Font& Font;
	sf::Text MenuText;

	sf::RectangleShape Background;
	sf::RectangleShape Container;

	sf::Texture LogoTexture;
	sf::Sprite LogoSprite;

	std::map<uint32, gui::Button*> Buttons;

private:

// Variables:

	Logger Log;
};