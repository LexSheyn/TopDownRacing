#include "../stdafx.h"
#include "PauseMenu.h"

//

PauseMenu::PauseMenu(sf::VideoMode videoMode, sf::Font& font)
	: Menu(videoMode, font)
{
	MenuText.setString("Pause");
	MenuText.setPosition
	(
		(Container.getPosition().x + (Container.getSize().x / 2.f)) - (MenuText.getGlobalBounds().width / 2.f),
		Container.getPosition().y + (MenuText.getGlobalBounds().height * 2.f)
	);
}

PauseMenu::~PauseMenu()
{
}


// Functions:s

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
