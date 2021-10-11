#pragma once

#include "../GUI/Button.h"

namespace gui
{
	class DropDownList
	{
	public:

	// Constructors and Destructor:

		DropDownList
		(
			const float x, const float y, const float width, const float height,
			sf::Font& font, std::string list[],
			uint32 numberOfElements, uint32 defaultIndex = 0
		);
		DropDownList
		(
			const float x, const float y, const float width, const float height,
			sf::VideoMode videoMode,
			sf::Font& font, std::string list[],
			uint32 numberOfElements, uint32 defaultIndex = 0
		);

		~DropDownList();

	// Functions:

		void Update(const sf::Vector2i& mousePosition, const float& dt);

		void Render(sf::RenderTarget* target);

	// Accessors:		

		const uint32& GetActiveElementId() const;

		const bool GetKeyTime();

	private:

	// Variables:

		sf::Clock KeyTimer;

		float KeyTimeMax;

		sf::Font& Font;

		gui::Button* ActiveElement;

		std::vector<gui::Button*> List;

		bool Showed;

		std::string StrWidth;

		std::string StrHeight;
	};
}