#pragma once

#include "../../GUI/DropDownList.h"

class Menu
{
public:

// Constructors and Destructor:

	Menu(sf::VideoMode& videoMode, sf::Font& font);

	virtual ~Menu();

// Functions:

	// Positions available from top to bottom: 0 - 7.
	void AddButton(const int32 index, const int32 position, sf::Texture* texture);

	// Pure virtual
	virtual void Update(const sf::Vector2i& mousePosition, const float& dt) = 0;
	
	// Pure virtual
	virtual void Render(sf::RenderTarget* target) = 0;

// Accessors:

	const bool IsButtonPressed(const int32 index);

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

	std::map<const int32, gui::Button*> Buttons;
	gui::Button* ButtonPtr[8];
	int32 ButtonPtrSize;

private:

// Private Functions:

	void InitVariables();

// Variables:

	Logger Log;
};