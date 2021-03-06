#include "../stdafx.h"
#include "DropDownList.h"

namespace gui
{
// Constructors and Destructor:

	DropDownList::DropDownList
	(
		const float x, const float y, const float width, const float height,
		sf::Clock& keyTimer, float& keyTimeMax,
		std::string defaultString,
		sf::Font& font, std::string list[],
		uint32 numberOfElements, uint32 defaultIndex
	) : Font(font), Showed(false), KeyTimer(keyTimer), KeyTimeMax(keyTimeMax)
	{
		ActiveElement = new gui::Button
		(
			x, y, width, height,
			Font, list[defaultIndex]
		);

		ActiveElement->SetString(defaultString);

		for (uint32 i = 0; i < numberOfElements; i++)
		{
			if (list[i] == defaultString)
			{
				ActiveElement->SetId(i);
			}

			List.push_back
			(
				new gui::Button
				(
					x, y + (static_cast<float>(i + 1u) * height), width, height,
					Font, list[i], i
				)
			);
		}
	}

	DropDownList::DropDownList
	(
		const float x, const float y, const float width, const float height,
		sf::Clock& keyTimer, float& keyTimeMax,
		sf::VideoMode videoMode, 
		sf::Font& font, std::string list[], 
		uint32 numberOfElements, uint32 defaultIndex
	) : Font(font), Showed(false), KeyTimer(keyTimer), KeyTimeMax(keyTimeMax)
	{
		ActiveElement = new gui::Button
		(
			x, y, width, height,
			Font, list[defaultIndex]
		);

		StrWidth = std::to_string(videoMode.width);
		StrHeight = std::to_string(videoMode.height);

		ActiveElement->SetString(StrWidth + " x " + StrHeight);

		for (uint32 i = 0; i < numberOfElements; i++)
		{
			if (list[i] == StrWidth + " x " + StrHeight)
			{
				ActiveElement->SetId(i);
			}

			List.push_back
			(
				new gui::Button
				(
					x, y + (static_cast<float>(i + 1u) * height), width, height,
					Font, list[i], i
				)
			);			
		}
	}
	
	DropDownList::~DropDownList()
	{
		// Deleting elements
		delete ActiveElement;

		for (auto*& element : List)
		{
			delete element;
		}
	}
	

// Functions:

	void DropDownList::Update(const sf::Vector2i& mousePosition, const float& dt)
	{
		// Active element
		ActiveElement->Update(mousePosition, dt);

		// Showing and hiding list
		if (ActiveElement->IsPressed() && GetKeyTime())
		{
			if (Showed)
			{
				Showed = false;
			}
			else
			{
				Showed = true;
			}
		}

		// When the list is showed up
		if (Showed)
		{
			for (auto& element : List)
			{
				element->Update(mousePosition, dt);

				if (element->IsPressed() && GetKeyTime())
				{
					Showed = false;

					ActiveElement->SetString(element->GetString());
					ActiveElement->SetId(element->GetId());
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && GetKeyTime())
			{
				Showed = false;
			}
		}
	}
	
	void DropDownList::Render(sf::RenderTarget* target)
	{
		ActiveElement->Render(target);

		if (Showed)
		{
			for (auto& element : List)
			{
				element->Render(target);
			}
		}
	}
	

// Accessors:

	const uint32& DropDownList::GetActiveElementId() const
	{
		return ActiveElement->GetId();
	}

	const bool DropDownList::GetKeyTime()
	{
		if (KeyTimer.getElapsedTime().asSeconds() >= KeyTimeMax)
		{
			KeyTimer.restart();

			return true;
		}

		return false;
	}
}