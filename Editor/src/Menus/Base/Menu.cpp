#include "../../stdafx.h"
#include "Menu.h"

//

Menu::Menu(sf::VideoMode& videoMode, sf::Font& font)
	: Font(font), Log(typeid(*this).name())
{
	// Background
	Background.setSize
	(
		sf::Vector2f
		(
			static_cast<float>(videoMode.width),
			static_cast<float>(videoMode.height)
		)
	);
	Background.setFillColor(sf::Color(20, 20, 20, 100));

	// Container
	Container.setSize
	(
		sf::Vector2f
		(
			static_cast<float>(videoMode.width) / 3.f,
			static_cast<float>(videoMode.height)
		)
	);
	Container.setFillColor(sf::Color(80, 20, 0, 100));

	// Text
	MenuText.setFont(Font);
	MenuText.setFillColor(sf::Color(100, 100, 100, 200));
	MenuText.setCharacterSize(gui::CalculateCharSize(4.f, videoMode));
	MenuText.setString("Menu");
	MenuText.setPosition
	(
		(Container.getPosition().x + (Container.getSize().x / 2.f)) - (MenuText.getGlobalBounds().width / 2.f),
		Container.getPosition().y + (MenuText.getGlobalBounds().height * 2.f)
	);
}

Menu::~Menu()
{
	for (auto& button : Buttons)
	{
		delete button.second;
	}

	Buttons.clear();
}


// Accessors:

const bool Menu::IsButtonPressed(const uint32 index)
{
	return Buttons[index]->IsPressed();
}


// Protected Funtions:

void Menu::InitTexture(sf::Texture& texture, const std::string& filePath)
{
	if (texture.loadFromFile(filePath))
	{
		Log.Trace("InitTexture::Texture loaded: " + filePath);
	}
	else
	{
		Log.Error("InitTexture::Faile to load: " + filePath);
	}
}
