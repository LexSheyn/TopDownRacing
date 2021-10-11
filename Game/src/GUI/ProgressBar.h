#pragma once

namespace gui
{
	class ProgressBar
	{
	public:

	// Constructors and Destructor::

		ProgressBar(const float x, const float y, const float width, const float height);

		~ProgressBar();

	// Functions:

		void Update(const int32 valueCurrent, const int32 valueMax, const float& dt);

		void Render(sf::RenderTarget* target);

	// Modifiers:

		void SetPosition(const float x, const float y);
		void SetPosition(const sf::Vector2f& position);

		void SetColorBack(const sf::Color& color);

		void SetColorFill(const sf::Color& color);

		void SetTextureBack(sf::Texture& texture);

		void SetTextureFill(sf::Texture& texture);

		void SetFont(sf::Font& font);

	private:

	// Variables:

		std::string String;
		sf::Text Text;
		sf::Font* Font;
		sf::RectangleShape Back;
		sf::RectangleShape Fill;
		sf::Texture BackTexture;
		sf::Texture FillTexture;
		float WidthMax;
		float Percent;
		float Color;
	};
}