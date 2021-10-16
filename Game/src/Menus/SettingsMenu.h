#pragma once

#include "Base/Menu.h"
#include "../Graphics/GraphicsSettings.h"

class SettingsMenu : public Menu
{
public:

// Constructors and Destructor:

	SettingsMenu(sf::RenderWindow* window, GraphicsSettings* graphicsSettings, sf::Font& font, sf::Clock& keyTimer, float& keyTimeMax);

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

	void InitOptions();

	void InitGui();

// Variables:

	Logger Log;

	// Buttons
	static const uint32 ButtonsAmount = 3u;

	gui::Button* ButtonPtr[ButtonsAmount];
	uint32 ButtonPtrSize;

	uint32 ButtonIndex[ButtonsAmount];
	uint32 ButtonIndexSize;

	sf::Texture* ButtonTexture[ButtonsAmount];
	uint32 ButtonTextureSize;

	enum Setting : uint32
	{
		RESOLUTION = 0, FULLSCREEN, FRAMERATE_LIMIT, VERTICAL_SYNC, MUSIC_VOLUME, SOUND_VOLUME
	};

	// Core
	sf::RenderWindow* Window;

	GraphicsSettings* GfxSettings;

	sf::Clock& KeyTimer;

	float& KeyTimeMax;

	// Settings
	static const uint32 SettingsAmount = 6u;

	sf::Text SettingsText[SettingsAmount];

	std::map<uint32, gui::DropDownList*> SettingsList;

	std::vector<sf::VideoMode> Resolution;
	std::vector<int32> Fullscreen;
	std::vector<uint32> FramerateLimit;
	std::vector<bool> VerticalSync;

	std::vector<std::string> Option[SettingsAmount];

	bool Opened;
};