#include "../stdafx.h"
#include "Button.h"

namespace gui
{
// Constructors and Destructor:

	gui::Button::Button(const float x, const float y, const float width, const float height, sf::Texture* texture, const uint32 id)
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

	Button::Button(const float x, const float y, const float width, const float height, sf::Font& font, const std::string& str, const uint32 id)
	{
		InitVariables();

		Shape.setPosition(x, y);
		Shape.setSize(sf::Vector2f(width, height));
		Shape.setOutlineThickness(-1.f);

		Font = &font;

		Text.setFont(*Font);
		Text.setCharacterSize(static_cast<uint32>(Shape.getSize().y / 1.5f));
		Text.setString(str);
		Text.setPosition((Shape.getPosition().x + (Shape.getGlobalBounds().width / 2.f)) - (Text.getGlobalBounds().width / 1.75f), Shape.getPosition().y + (Shape.getGlobalBounds().height / 20.f));

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
			ButtonStatus = Status::COVERED;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				ButtonStatus = Status::PRESSED;
			}
		}
		else
		{
			ButtonStatus = Status::IDLE;
		}

		switch (ButtonStatus)
		{
			case Status::IDLE:
			{				
				if (Font)
				{					
					Text.setFillColor(sf::Color(250, 50, 50));
					Shape.setOutlineColor(sf::Color(250, 50, 50));
					Shape.setFillColor(sf::Color(100, 50, 50));
				}
				else
				{
					Shape.setFillColor(sf::Color(150, 50, 50));
				}

				break;
			}			

			case Status::COVERED:
			{
				Shape.setFillColor(sf::Color(250, 50, 50));
				
				if (Font)
				{
					Text.setFillColor(sf::Color(50, 50, 50));
					Shape.setOutlineColor(sf::Color(150, 50, 50));
				}

				break;
			}			

			case Status::PRESSED:
			{				
				if (Font)
				{
					Text.setFillColor(sf::Color(250, 250, 250));
					Shape.setOutlineColor(sf::Color(200, 50, 50));
					Shape.setFillColor(sf::Color(150, 50, 50));
				}
				else
				{
					Shape.setFillColor(sf::Color(100, 50, 50));
				}

				break;
			}
		}

		Text.setPosition((Shape.getPosition().x + (Shape.getGlobalBounds().width / 2.f)) - (Text.getGlobalBounds().width / 1.85f), Shape.getPosition().y + (Shape.getGlobalBounds().height / 20.f));
	}

	void Button::Render(sf::RenderTarget* target)
	{
		target->draw(Shape);
		
		if (Font)
		{
			target->draw(Text);
		}
	}


// Accessors:

	const bool Button::IsPressed() const
	{
		if (ButtonStatus == Status::PRESSED)
		{
			return true;
		}

		return false;
	}

	const std::string Button::GetString() const
	{
		return Text.getString();
	}

	const uint32& Button::GetId() const
	{
		return Id;
	}


// Modifiers:

	void Button::SetString(const std::string& str)
	{
		Text.setString(str);
	}

	void Button::SetId(const uint32 id)
	{
		Id = id;
	}


// Private Functions:

	void Button::InitVariables()
	{
		Font = nullptr;

		ButtonStatus = Status::IDLE;

		Id = 0;
	}
}