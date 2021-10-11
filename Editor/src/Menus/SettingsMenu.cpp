#include "../stdafx.h"
#include "SettingsMenu.h"

// Constructors and Destructor:

SettingsMenu::SettingsMenu(sf::RenderWindow* window, GraphicsSettings* graphicsSettings, sf::Font& font)
	: Menu(graphicsSettings->Resolution, font), Window(window), GfxSettings(graphicsSettings), Opened(false)
{
	InitVideoModes();

	Container.setPosition(sf::Vector2f(static_cast<float>(GfxSettings->Resolution.width) / 3.f, 0.f));
	Container.setSize(sf::Vector2f((static_cast<float>(GfxSettings->Resolution.width) / 3.f) * 2.f, static_cast<float>(GfxSettings->Resolution.height)));
	Container.setOutlineColor(sf::Color(200, 20, 0, 200));
	Container.setOutlineThickness(-1.f);

	MenuText.setString("Settings");
	MenuText.setPosition
	(
		(Container.getPosition().x + (Container.getSize().x / 2.f)) - (MenuText.getGlobalBounds().width / 2.f),
		Container.getPosition().y + (MenuText.getGlobalBounds().height * 2.f)
	);

	// Settings text
	for (uint32 i = 0; i < sizeof(SettingsText) / sizeof(*SettingsText); i++)
	{
		SettingsText[i].setFont(Font);
		SettingsText[i].setCharacterSize(gui::CalculateCharSize(3.f, GfxSettings->Resolution));
		SettingsText[i].setPosition(Container.getPosition().x + (Container.getSize().x / 20.f), Container.getPosition().y + 100.f * static_cast<float>(i));
	}

	SettingsText[Setting::Resolution].setString("Resolution");
	SettingsText[Setting::Fullscreen].setString("Fullscreen");
	SettingsText[Setting::FramerateLimit].setString("Framerate limit");
	SettingsText[Setting::VerticalSync].setString("Vertical sync");
	SettingsText[Setting::MusicVolume].setString("Music volume");
	SettingsText[Setting::SoundVolume].setString("Sound volume");

	ResolutionList = new gui::DropDownList
	(
		1000.f, 200.f,
		gui::PercentToX(10.f, GfxSettings->Resolution), gui::PercentToY(3.f, GfxSettings->Resolution),
		GfxSettings->Resolution, Font,
		VideoModeString.data(), static_cast<uint32>(VideoModeString.size()));
}

SettingsMenu::~SettingsMenu()
{
	// Deleting resolution list
	delete ResolutionList;
}


// Functions:

void SettingsMenu::Open()
{
	Opened = true;
}

void SettingsMenu::Close()
{
	Opened = false;
}

void SettingsMenu::Update(const sf::Vector2i& mousePosition, const float& dt)
{
	if (Opened)
	{
		// DropDownList
		ResolutionList->Update(mousePosition, dt);

		// Buttons:
		for (auto& button : Buttons)
		{
			button.second->Update(mousePosition, dt);
		}
	}
}

void SettingsMenu::Render(sf::RenderTarget* target)
{
	if (Opened)
	{
		target->draw(Background);

		target->draw(Container);

		target->draw(MenuText);

		// Settings text
		for (auto& text : SettingsText)
		{
			target->draw(text);
		}

		// Resolution
		ResolutionList->Render(target);

		// Buttons:
		for (auto& button : Buttons)
		{
			button.second->Render(target);
		}
	}
}


// Accessors:

const bool& SettingsMenu::IsOpen() const
{
	return Opened;
}


// Private Functions:

void SettingsMenu::InitVideoModes()
{
	VideoMode.push_back(sf::VideoMode(1920, 1080));
	VideoMode.push_back(sf::VideoMode(1904, 1071));

	VideoMode.push_back(sf::VideoMode(1600, 900));
	VideoMode.push_back(sf::VideoMode(1584, 891));

	VideoMode.push_back(sf::VideoMode(1280, 720));
	VideoMode.push_back(sf::VideoMode(1264, 711));

	for (auto& mode : VideoMode)
	{
		VideoModeString.push_back(std::to_string(mode.width) + " x " + std::to_string(mode.height));
	}
}
