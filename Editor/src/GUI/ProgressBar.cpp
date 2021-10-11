#include "../stdafx.h"
#include "ProgressBar.h"

namespace gui
{

// Constructors and Destructor:

	ProgressBar::ProgressBar(const float x, const float y, const float width, const float height)
		: Font(nullptr), WidthMax(width), Percent(0.f), Color(254.f)
	{
		Back.setSize(sf::Vector2f(width, height));
		Back.setPosition(x, y);
		Back.setFillColor(sf::Color(50, 50, 50, 200));

		Fill.setSize(Back.getSize());
		Fill.setPosition(Back.getPosition());
		Fill.setFillColor(sf::Color(250, 20, 20, 200));

		Text.setPosition
		(
			Back.getPosition().x + (Back.getGlobalBounds().width / 20.f),
			Back.getPosition().y + (Back.getGlobalBounds().height / 20.f)
		);
		Text.setCharacterSize(static_cast<uint32>(Back.getSize().y / 1.5f));
	}
	
	ProgressBar::~ProgressBar()
	{

	}
	

// Functions:

	void ProgressBar::Update(const int32 valueCurrent, const int32 valueMax, const float& dt)
	{
		Percent = static_cast<float>(valueCurrent) / static_cast<float>(valueMax);

		Fill.setSize(sf::Vector2f(static_cast<float>(std::floor(WidthMax * Percent)), Fill.getSize().y));

		if (Fill.getSize().x < 0.f)
		{
			Fill.setSize(sf::Vector2f(0.f, Fill.getSize().y));
		}

		if (Font)
		{
			String = std::to_string(valueCurrent) + " / " + std::to_string(valueMax);
			Text.setString(String);
		}

		Fill.setFillColor(sf::Color(static_cast<uint8>(Color - std::pow(Color, Percent)), static_cast<uint8>(Color * Percent), 20, 200));
	}
	
	void ProgressBar::Render(sf::RenderTarget* target)
	{
		target->draw(Back);

		target->draw(Fill);

		if (Font)
		{
			target->draw(Text);
		}
	}
	
	
// Modifiers:

	void ProgressBar::SetPosition(const float x, const float y)
	{
		Back.setPosition(x, y);

		Fill.setPosition(Back.getPosition());
	}
	
	void ProgressBar::SetPosition(const sf::Vector2f& position)
	{
		Back.setPosition(position);

		Fill.setPosition(Back.getPosition());
	}
	
	void ProgressBar::SetColorBack(const sf::Color& color)
	{
		Back.setFillColor(color);
	}
	
	void ProgressBar::SetColorFill(const sf::Color& color)
	{
		Fill.setFillColor(color);
	}
	
	void ProgressBar::SetTextureBack(sf::Texture& texture)
	{
		Back.setTexture(&texture);
	}
	
	void ProgressBar::SetTextureFill(sf::Texture& texture)
	{
		Fill.setTexture(&texture);
	}
	
	void ProgressBar::SetFont(sf::Font& font)
	{
		Font = &font;

		Text.setFont(*Font);
	}
}