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

	// Positions available from left to right: 0 - 2.
	void AddButton(const uint32 index, const uint32 position, sf::Texture* texture);

	void ResetWindow();

	void ResetGui() override;

	void Update(const sf::Vector2i& mousePosition, const float& dt) override;

	void Render(sf::RenderTarget* target) override;

	// Accessors:

	const bool& IsOpen() const;

private:

	// Private Functions:

	void InitVariables();

	void InitVideoModes();

	void InitGui();

	// Variables:

	Logger Log;

	static const uint32 ButtonsAmount = 3u;

	gui::Button* ButtonPtr[ButtonsAmount];
	uint32 ButtonPtrSize;

	uint32 ButtonIndex[ButtonsAmount];
	uint32 ButtonIndexSize;

	sf::Texture* ButtonTexture[ButtonsAmount];
	uint32 ButtonTextureSize;

	enum Setting : uint32
	{
		Resolution = 0, Fullscreen, FramerateLimit, VerticalSync, MusicVolume, SoundVolume
	};

	sf::RenderWindow* Window;

	GraphicsSettings* GfxSettings;

	sf::Text SettingsText[6];

	std::map<uint32, gui::DropDownList*> SettingsList;

	std::vector<sf::VideoMode> VideoMode;
	std::vector<std::string> VideoModeString;

	bool Opened;
};