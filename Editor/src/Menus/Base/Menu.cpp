#include "../../stdafx.h"
#include "Menu.h"

//

Menu::Menu(sf::VideoMode& videoMode, sf::Font& font)
	: Font(font), Log(typeid(*this).name())
{
	InitVariables();

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
	// Deleting buttons
	for (auto& buttonPtr : ButtonPtr)
	{
		buttonPtr = nullptr;
	}

	for (auto& button : Buttons)
	{
		delete button.second;
	}

	Buttons.clear();
}


// Functions:

void Menu::AddButton(const int32 index, const int32 position, sf::Texture* texture)
{
	if (position >= 0 && position < ButtonPtrSize)
	{
		if (ButtonPtr[position] == nullptr)
		{
			float buttonWidth = Container.getSize().x / 3.f;
			float buttonHeight = Container.getSize().y / 24.f;

			Buttons[index] = new gui::Button
			(
				Container.getPosition().x + Container.getSize().x / 3.f, 
				Container.getPosition().y + Container.getSize().y / 5.f + buttonHeight * 1.5f * static_cast<float>(position),
				buttonWidth, 
				buttonHeight,
				texture,
				static_cast<uint32>(position)
			);

			ButtonPtr[position] = Buttons[index];
		}
		else
		{
			Log.Warning("AddButton::Position is already taken, button has not been created: " + std::to_string(index));
		}
	}
	else
	{
		Log.Error("AddButton::Position is out of range");
	}
}


// Accessors:

const bool Menu::IsButtonPressed(const int32 index)
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


// Private Functions:

void Menu::InitVariables()
{
	ButtonPtrSize = static_cast<int32>(sizeof(ButtonPtr) / sizeof(*ButtonPtr));

	for (auto& buttonPtr : ButtonPtr)
	{
		buttonPtr = nullptr;
	}
}
