#include "../stdafx.h"
#include "SettingsMenu.h"

// Constructors and Destructor:

SettingsMenu::SettingsMenu(sf::RenderWindow* window, GraphicsSettings* graphicsSettings, sf::Font& font, sf::Clock& keyTimer, float& keyTimeMax)
	: Menu(graphicsSettings->Resolution, font), Window(window), GfxSettings(graphicsSettings), Opened(false), KeyTimer(keyTimer), KeyTimeMax(keyTimeMax), Log(typeid(*this).name())
{
	InitVariables();

	InitOptions();

	InitGui();
}

SettingsMenu::~SettingsMenu()
{
	// Deleting lists
	for (auto& list : SettingsList)
	{
		delete list.second;
	}

	SettingsList.clear();
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

void SettingsMenu::AddButton(const uint32 index, const uint32 position, sf::Texture* texture)
{
	if (position >= 0 && position < ButtonPtrSize)
	{
		if (ButtonPtr[position] == nullptr)
		{
			float buttonWidth = Container.getSize().x / 6.f;
			float buttonHeight = Container.getSize().y / 24.f;
			
			Buttons[index] = new gui::Button
			(
				Container.getPosition().x + Container.getSize().x / 12.f + buttonWidth * static_cast<float>(position),
				Container.getPosition().y + Container.getSize().y / 4.f * 3.f,
				buttonWidth,
				buttonHeight,
				texture,
				position
			);

			ButtonPtr[position] = Buttons[index];
			ButtonTexture[position] = texture;
			ButtonIndex[position] = index;
		}
		else
		{
			Log.Warning("AddButton::Position is already taken, button has not been created: " + std::to_string(index));
		}
	}
	else
	{
		Log.Error("AddButton::Position is out of range");
	}
}

void SettingsMenu::ResetWindow()
{
	GfxSettings->Resolution = Resolution[SettingsList[RESOLUTION]->GetActiveElementId()];
	GfxSettings->Fullscreen = Fullscreen[SettingsList[FULLSCREEN]->GetActiveElementId()];
	GfxSettings->FramerateLimit = FramerateLimit[SettingsList[FRAMERATE_LIMIT]->GetActiveElementId()];
	GfxSettings->VerticalSync = VerticalSync[SettingsList[VERTICAL_SYNC]->GetActiveElementId()];

	GfxSettings->Save("../Config/graphics.ini");
	GfxSettings->Load("../Config/graphics.ini");

	Window->create
	(
		GfxSettings->Resolution,
		GfxSettings->Title,
		GfxSettings->Style,
		GfxSettings->ContextSettings
	);

	Window->setFramerateLimit(GfxSettings->FramerateLimit);
	Window->setVerticalSyncEnabled(GfxSettings->VerticalSync);
	Window->setMouseCursorGrabbed(GfxSettings->CursorGrabbing);
}

void SettingsMenu::ResetGui()
{
	// Deleting lists
	for (auto& list : SettingsList)
	{
		delete list.second;
	}

	SettingsList.clear();

	InitGui();

	// Buttons
	for (uint32 i = 0; i < ButtonPtrSize; i++)
	{
		if (ButtonPtr[i])
		{
			ButtonPtr[i] = nullptr;

			delete Buttons[ButtonIndex[i]];

			float buttonWidth = Container.getSize().x / 6.f;
			float buttonHeight = Container.getSize().y / 24.f;

			Buttons[ButtonIndex[i]] = new gui::Button
			(
				Container.getPosition().x + Container.getSize().x / 12.f + buttonWidth * static_cast<float>(i),
				Container.getPosition().y + Container.getSize().y / 4.f * 3.f,
				buttonWidth,
				buttonHeight,
				ButtonTexture[i],
				i
			);

			ButtonPtr[i] = Buttons[ButtonIndex[i]];
		}
	}
}

void SettingsMenu::Update(const sf::Vector2i& mousePosition, const float& dt)
{
	if (Opened)
	{
		// Drop down lists
		for (auto& list : SettingsList)
		{
			list.second->Update(mousePosition, dt);
		}
	}
		// Buttons:
		for (auto& button : Buttons)
		{
			button.second->Update(mousePosition, dt);
		}
}

void SettingsMenu::Render(sf::RenderTarget* target)
{
	if (Opened)
	{
	//	target->draw(Background);

		target->draw(Container);

		target->draw(MenuText);

		// Settings text
		for (auto& text : SettingsText)
		{
			target->draw(text);
		}

		// Drop down lists Reversed Rendering Order
		for (auto list = SettingsList.rbegin(); list != SettingsList.rend(); list++)
		{
			list->second->Render(target);
		}

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

void SettingsMenu::InitVariables()
{
	// Buttons
	ButtonPtrSize = static_cast<uint32>(sizeof(ButtonPtr) / sizeof(*ButtonPtr));

	for (auto& buttonPtr : ButtonPtr)
	{
		buttonPtr = nullptr;
	}

	ButtonIndexSize = sizeof(ButtonIndex) / sizeof(*ButtonIndex);

	for (auto& buttonIndex : ButtonIndex)
	{
		buttonIndex = UINT_MAX;
	}

	// Textures
	ButtonTextureSize = static_cast<uint32>(sizeof(ButtonTexture) / sizeof(*ButtonTexture));

	for (auto& buttonTexture : ButtonTexture)
	{
		buttonTexture = nullptr;
	}
}

void SettingsMenu::InitOptions()
{
	// Resolution
	Resolution.push_back(sf::VideoMode(1920, 1080));
	Resolution.push_back(sf::VideoMode(1904, 1071));
	Resolution.push_back(sf::VideoMode(1600, 900));
	Resolution.push_back(sf::VideoMode(1584, 891));
	Resolution.push_back(sf::VideoMode(1280, 720));
	Resolution.push_back(sf::VideoMode(1264, 711));

	for (auto& resolution : Resolution)
	{
		Option[RESOLUTION].push_back(std::to_string(resolution.width) + " x " + std::to_string(resolution.height));
	}

	// Fullscreen
	Fullscreen.push_back(0);
	Fullscreen.push_back(1);
	Fullscreen.push_back(2);

	Option[FULLSCREEN].push_back("Window");
	Option[FULLSCREEN].push_back("Fullscreen");
	Option[FULLSCREEN].push_back("Borderless");

	// Framerate limit
	FramerateLimit.push_back(30);
	FramerateLimit.push_back(60);
	FramerateLimit.push_back(0);

	Option[FRAMERATE_LIMIT].push_back("30");
	Option[FRAMERATE_LIMIT].push_back("60");
	Option[FRAMERATE_LIMIT].push_back("OFF");

	// Vertical sync
	VerticalSync.push_back(false);
	VerticalSync.push_back(true);

	Option[VERTICAL_SYNC].push_back("OFF");
	Option[VERTICAL_SYNC].push_back("ON");
}

void SettingsMenu::InitGui()
{
	// Container
	Container.setPosition(sf::Vector2f(static_cast<float>(GfxSettings->Resolution.width) / 3.f, 0.f));
	Container.setSize(sf::Vector2f((static_cast<float>(GfxSettings->Resolution.width) / 3.f) * 2.f, static_cast<float>(GfxSettings->Resolution.height)));
	Container.setOutlineColor(sf::Color(200, 20, 0, 200));
	Container.setOutlineThickness(-1.f);

	// Text
	MenuText.setCharacterSize(gui::CalculateCharSize(4.f, GfxSettings->Resolution));
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
		SettingsText[i].setPosition
		(
			Container.getPosition().x + (Container.getSize().x / 12.f),
			Container.getPosition().y + (Container.getSize().y / 10.f) + (gui::PercentToY(4.f, GfxSettings->Resolution) * static_cast<float>(i + 1u) * 2.f)
		);
	}

	SettingsText[RESOLUTION].setString("Resolution");
	SettingsText[FULLSCREEN].setString("Fullscreen");
	SettingsText[FRAMERATE_LIMIT].setString("Framerate limit");
	SettingsText[VERTICAL_SYNC].setString("Vertical sync");
	SettingsText[MUSIC_VOLUME].setString("Music volume");
	SettingsText[SOUND_VOLUME].setString("Sound volume");

	// Resolution
	SettingsList[RESOLUTION] = new gui::DropDownList
	(
		SettingsText[RESOLUTION].getPosition().x + (Container.getSize().x / 12.f * 4.f), SettingsText[RESOLUTION].getPosition().y,
		gui::PercentToX(13.f, GfxSettings->Resolution), gui::PercentToY(4.0f, GfxSettings->Resolution),
		KeyTimer, KeyTimeMax,
		GfxSettings->Resolution, Font,
		Option[RESOLUTION].data(), static_cast<uint32>(Option[RESOLUTION].size())
	);

	// Fullscreen
	SettingsList[FULLSCREEN] = new gui::DropDownList
	(
		SettingsText[FULLSCREEN].getPosition().x + (Container.getSize().x / 12.f * 4.f), SettingsText[FULLSCREEN].getPosition().y,
		gui::PercentToX(13.f, GfxSettings->Resolution), gui::PercentToY(4.0f, GfxSettings->Resolution),
		KeyTimer, KeyTimeMax,
		Option[FULLSCREEN][GfxSettings->Fullscreen],
		Font, Option[FULLSCREEN].data(), static_cast<uint32>(Option[FULLSCREEN].size())
	);

	// Framerate limit
	std::string defaultString;

	for (uint32 i = 0; i < FramerateLimit.size(); i++)
	{
		if (FramerateLimit[i] == GfxSettings->FramerateLimit)
		{
			defaultString = Option[FRAMERATE_LIMIT][i];
		}
	}

	SettingsList[FRAMERATE_LIMIT] = new gui::DropDownList
	(
		SettingsText[FRAMERATE_LIMIT].getPosition().x + (Container.getSize().x / 12.f * 4.f), SettingsText[FRAMERATE_LIMIT].getPosition().y,
		gui::PercentToX(13.f, GfxSettings->Resolution), gui::PercentToY(4.0f, GfxSettings->Resolution),
		KeyTimer, KeyTimeMax,
		defaultString,
		Font, Option[FRAMERATE_LIMIT].data(), static_cast<uint32>(Option[FRAMERATE_LIMIT].size())
	);

	// Vertical sync
	SettingsList[VERTICAL_SYNC] = new gui::DropDownList
	(
		SettingsText[VERTICAL_SYNC].getPosition().x + (Container.getSize().x / 12.f * 4.f), SettingsText[VERTICAL_SYNC].getPosition().y,
		gui::PercentToX(13.f, GfxSettings->Resolution), gui::PercentToY(4.0f, GfxSettings->Resolution),
		KeyTimer, KeyTimeMax,
		Option[VERTICAL_SYNC][GfxSettings->VerticalSync],
		Font, Option[VERTICAL_SYNC].data(), static_cast<uint32>(Option[VERTICAL_SYNC].size())
	);

//	// Music volume
//	SettingsList[MusicVolume] = new gui::DropDownList
//	(
//		SettingsText[MusicVolume].getPosition().x + (Container.getSize().x / 12.f * 4.f), SettingsText[MusicVolume].getPosition().y,
//		gui::PercentToX(13.f, GfxSettings->Resolution), gui::PercentToY(4.0f, GfxSettings->Resolution),
//		Font, Option[MusicVolume].data(), static_cast<uint32>(Option[MusicVolume].size())
//	);
//
//	// Sount volume
//	SettingsList[SoundVolume] = new gui::DropDownList
//	(
//		SettingsText[SoundVolume].getPosition().x + (Container.getSize().x / 12.f * 4.f), SettingsText[SoundVolume].getPosition().y,
//		gui::PercentToX(13.f, GfxSettings->Resolution), gui::PercentToY(4.0f, GfxSettings->Resolution),
//		Font, Option[SoundVolume].data(), static_cast<uint32>(Option[SoundVolume].size())
//	);
}
