#pragma once

#include "Base/Menu.h"
#include "../Graphics/GraphicsSettings.h"

class SettingsMenu : public Menu
{
public:

// Constructors and Destructor:

	SettingsMenu(sf::RenderWindow* window, GraphicsSettings* graphicsSettings, sf::Font& font);

	~SettingsMenu();

// Functions:

	void Open();

	void Close();

	void Update(const sf::Vector2i& mousePosition, const float& dt) override;

	void Render(sf::RenderTarget* target) override;

// Accessors:

	const bool& IsOpen() const;

private:

// Private Functions:

	void InitVideoModes();

// Variables:

	enum Setting : uint32
	{
		Resolution = 0, Fullscreen, FramerateLimit, VerticalSync, MusicVolume, SoundVolume
	};

	sf::RenderWindow* Window;

	GraphicsSettings* GfxSettings;

	sf::Text SettingsText[6];

	gui::DropDownList* ResolutionList;

	std::vector<sf::VideoMode> VideoMode;
	std::vector<std::string> VideoModeString;

	bool Opened;
};