#pragma once

// Statuses

enum class ButtonStatus : int32
{
	Idle = 0, Covered, Pressed
};

namespace gui
{
	class Button
	{
	public:

	// Constructors and Destructor:

		Button(const float x, const float y, const float width, const float height, const uint32 id, sf::Texture* texture);

		~Button();

	// Functions:

		void Update(const sf::Vector2i& mousePosition, const float& dt);

		void Render(sf::RenderTarget* target);

	// Accessors:

		const bool IsPressed() const;

		const uint32& GetId() const;

	private:

	// Private Functions:

		void InitVariables();

	// Variables:

		sf::RectangleShape Shape;

		ButtonStatus ButtonStatus;

		uint32 Id;
	};
}
