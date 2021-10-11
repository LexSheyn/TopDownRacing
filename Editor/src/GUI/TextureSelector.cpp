#include "../stdafx.h"
#include "TextureSelector.h"

namespace gui
{
// Constructors and Destructor:

	TextureSelector::TextureSelector(float x, float y, float gridSize, const sf::Texture& textureSheet)
	{
		InitVariables();

		GridSize = gridSize;
		float offset = gridSize;

		Sheet.setTexture(textureSheet);
		Sheet.setPosition(x + offset, y);

		Bounds.setSize(sf::Vector2f(Sheet.getGlobalBounds().width, Sheet.getGlobalBounds().height));
		Bounds.setPosition(x + offset, y);
		Bounds.setFillColor(sf::Color(50, 50, 50, 100));
		Bounds.setOutlineThickness(1.f);
		Bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

		Selector.setPosition(x, y);
		Selector.setSize(sf::Vector2f(gridSize, gridSize));
		Selector.setFillColor(sf::Color::Transparent);
		Selector.setOutlineThickness(-1.f);
		Selector.setOutlineColor(sf::Color::Red);

		TextureRect.width = static_cast<int32>(gridSize);
		TextureRect.height = static_cast<int32>(gridSize);
	}

	TextureSelector::~TextureSelector()
	{
	}

	void TextureSelector::Show()
	{
		Visible = true;
	}

	void TextureSelector::Hide()
	{
		Visible = false;

		Active = false;
	}

// Functions:

	void TextureSelector::Update(const sf::Vector2i& mousePositionWindow, const float& dt)
	{
		if (Visible)
		{
			if (Bounds.getGlobalBounds().contains(sf::Vector2f(mousePositionWindow)))
			{
				Active = true;
								
				MousePositionGrid.x = (mousePositionWindow.x - static_cast<int32>(Bounds.getPosition().x)) / static_cast<int32>(GridSize);
				MousePositionGrid.y = (mousePositionWindow.y - static_cast<int32>(Bounds.getPosition().y)) / static_cast<int32>(GridSize);

				Selector.setPosition
				(
					Bounds.getPosition().x + (static_cast<float>(MousePositionGrid.x) * GridSize),
					Bounds.getPosition().y + (static_cast<float>(MousePositionGrid.y) * GridSize)
				);
			}
			else
			{
				Active = false;
			}

			TextureRect.left = static_cast<int32>(Selector.getPosition().x - Bounds.getPosition().x);
			TextureRect.top = static_cast<int32>(Selector.getPosition().y - Bounds.getPosition().y);
		}
	}

	void TextureSelector::Render(sf::RenderTarget* target)
	{
		if (Visible)
		{
			target->draw(Bounds);
			target->draw(Sheet);

			if (Active)
			{
				target->draw(Selector);
			}
		}
	}

// Accessors:

	const bool& TextureSelector::IsActive() const
	{
		return Active;
	}

	const bool& TextureSelector::IsVisible() const
	{
		return Visible;
	}

	const sf::IntRect& TextureSelector::GetTextureRect() const
	{
		return TextureRect;
	}

// Private Functions:

	void TextureSelector::InitVariables()
	{
		Active = false;
		Visible = true;
	}
}