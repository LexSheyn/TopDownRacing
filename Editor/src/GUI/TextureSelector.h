#pragma once

#include "Button.h"

namespace gui
{
	class TextureSelector
	{
	public:

	// Constructors and Destructor:

		TextureSelector(float x, float y, float gridSize, const sf::Texture& textureSheet);

		~TextureSelector();

	// Functions:

		void Show();
		
		void Hide();

		void Update(const sf::Vector2i& mousePositionWindow, const float& dt);

		void Render(sf::RenderTarget* target);

	// Accessors:

		const bool& IsActive() const;

		const bool& IsVisible() const;

		const sf::IntRect& GetTextureRect() const;

	private:

	// Private Functions:

		void InitVariables();

	// Variables:

		float GridSize;
		bool Active;
		bool Visible;
		sf::RectangleShape Bounds;
		sf::Sprite Sheet;
		sf::RectangleShape Selector;
		sf::Vector2i MousePositionGrid;
		sf::IntRect TextureRect;
	};
}