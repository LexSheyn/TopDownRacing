#pragma once

namespace gui
{
	class Button
	{
	public:

	// Constructors and Destructor:

		Button(const float x, const float y, const float width, const float height, sf::Texture* texture, const uint32 id = 0);
		Button(const float x, const float y, const float width, const float height, sf::Font& font, const std::string& str, const uint32 id = 0);

		~Button();

	// Functions:

		void Update(const sf::Vector2i& mousePosition, const float& dt);

		void Render(sf::RenderTarget* target);

	// Accessors:

		const bool IsPressed() const;

		const std::string GetString() const;

		const uint32& GetId() const;

	// Modifiers:

		void SetString(const std::string& str);

		void SetId(const uint32 id);

	private:

	// Private Functions:

		void InitVariables();

	// Variables:

		// Statuses
		enum class Status : int32
		{
			IDLE = 0, COVERED, PRESSED
		};

		sf::RectangleShape Shape;

		sf::Font* Font;

		sf::Text Text;

		Status ButtonStatus;

		uint32 Id;
	};
}
