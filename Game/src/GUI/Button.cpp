#include "../stdafx.h"
#include "Button.h"

namespace gui
{
// Constructors and Destructor:

	gui::Button::Button(const float x, const float y, const float width, const float height, const uint32 id, sf::Texture* texture)
	{
		InitVariables();

		Shape.setPosition(x, y);
		Shape.setSize(sf::Vector2f(width, height));

		if (texture)
		{
			Shape.setTexture(texture);
		}

		Id = id;
	}

	gui::Button::~Button()
	{

	}


// Functions:

	void Button::Update(const sf::Vector2i& mousePosition, const float& dt)
	{
		if (Shape.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
		{
			ButtonStatus = ButtonStatus::Covered;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				ButtonStatus = ButtonStatus::Pressed;
			}
		}
		else
		{
			ButtonStatus = ButtonStatus::Idle;
		}

		switch (ButtonStatus)
		{
			case ButtonStatus::Idle:
			{
				Shape.setFillColor(sf::Color(150, 50, 50));

				break;
			}			

			case ButtonStatus::Covered:
			{
				Shape.setFillColor(sf::Color(250, 50, 50));

				break;
			}			

			case ButtonStatus::Pressed:
			{
				Shape.setFillColor(sf::Color(100, 50, 50));

				break;
			}
		}
	}

	void Button::Render(sf::RenderTarget* target)
	{
		target->draw(Shape);
	}


// Accessors:

	const bool Button::IsPressed() const
	{
		if (ButtonStatus == ButtonStatus::Pressed)
		{
			return true;
		}

		return false;
	}

	const uint32& Button::GetId() const
	{
		return Id;
	}


// Private Functions:

	void Button::InitVariables()
	{
		ButtonStatus = ButtonStatus::Idle;

		Id = 0;
	}
}