#include "../stdafx.h"
#include "PauseMenu.h"

//

PauseMenu::PauseMenu(sf::VideoMode& videoMode, sf::Font& font)
	: Menu(videoMode, font), VideoMode(videoMode), Log(typeid(*this).name())
{
	InitVariables();

	InitGui();
}

PauseMenu::~PauseMenu()
{
}


// Functions:s

void PauseMenu::AddButton(const uint32 index, const uint32 position, sf::Texture* texture)
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
				(position)
			);

			ButtonPtr[position] = Buttons[index];
			ButtonTexture[position] = texture;
			ButtonIndex[position] = index;
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

void PauseMenu::ResetGui()
{
	InitGui();

	// Buttons
	for (uint32 i = 0; i < ButtonPtrSize; i++)
	{
		if (ButtonPtr[i])
		{
			ButtonPtr[i] = nullptr;

			delete Buttons[ButtonIndex[i]];

			float buttonWidth = Container.getSize().x / 3.f;
			float buttonHeight = Container.getSize().y / 24.f;

			Buttons[ButtonIndex[i]] = new gui::Button
			(
				Container.getPosition().x + Container.getSize().x / 3.f,
				Container.getPosition().y + Container.getSize().y / 5.f + buttonHeight * 1.5f * static_cast<float>(i),
				buttonWidth,
				buttonHeight,
				ButtonTexture[i],
				i
			);

			ButtonPtr[i] = Buttons[ButtonIndex[i]];
		}
	}
}

void PauseMenu::Update(const sf::Vector2i& mousePosition, const float& dt)
{
	// Buttons:
	for (auto& button : Buttons)
	{
		button.second->Update(mousePosition, dt);
	}
}

void PauseMenu::Render(sf::RenderTarget* target)
{
	target->draw(Background);

	target->draw(Container);

	target->draw(MenuText);

	//

	for (auto& button : Buttons)
	{
		button.second->Render(target);
	}
}


// Private Functions:

void PauseMenu::InitVariables()
{
	ButtonPtrSize = static_cast<uint32>(sizeof(ButtonPtr) / sizeof(*ButtonPtr));

	for (auto& buttonPtr : ButtonPtr)
	{
		buttonPtr = nullptr;
	}

	ButtonIndexSize = sizeof(ButtonIndex) / sizeof(*ButtonIndex);

	for (auto& buttonIndex : ButtonIndex)
	{
		buttonIndex = UINT_MAX;
	}

	// Textures
	ButtonTextureSize = static_cast<uint32>(sizeof(ButtonTexture) / sizeof(*ButtonTexture));

	for (auto& buttonTexture : ButtonTexture)
	{
		buttonTexture = nullptr;
	}
}

void PauseMenu::InitGui()
{
	// Background
	Background.setSize
	(
		sf::Vector2f
		(
			static_cast<float>(VideoMode.width),
			static_cast<float>(VideoMode.height)
		)
	);

	// Container
	Container.setSize
	(
		sf::Vector2f
		(
			static_cast<float>(VideoMode.width) / 3.f,
			static_cast<float>(VideoMode.height)
		)
	);

	// Text
	MenuText.setCharacterSize(gui::CalculateCharSize(4.f, VideoMode));
	MenuText.setString("Pause");
	MenuText.setPosition
	(
		(Container.getPosition().x + (Container.getSize().x / 2.f)) - (MenuText.getGlobalBounds().width / 2.f),
		Container.getPosition().y + (MenuText.getGlobalBounds().height * 2.f)
	);
}
