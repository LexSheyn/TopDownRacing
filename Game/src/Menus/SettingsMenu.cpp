#include "../stdafx.h"
#include "SettingsMenu.h"

// Constructors and Destructor:

SettingsMenu::SettingsMenu(sf::RenderWindow* window, GraphicsSettings* graphicsSettings, sf::Font& font)
	: Menu(graphicsSettings->Resolution, font), Window(window), GfxSettings(graphicsSettings), Opened(false), Log(typeid(*this).name())
{
	InitVariables();

	InitVideoModes();

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
	GfxSettings->Resolution = VideoMode[SettingsList[Resolution]->GetActiveElementId()];

	Window->create
	(
		GfxSettings->Resolution,
		GfxSettings->Title,
		GfxSettings->Style,
		GfxSettings->ContextSettings
	);

	Window->setFramerateLimit(GfxSettings->FrameRateLimit);
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

		// Resolution
		for (auto& list : SettingsList)
		{
			list.second->Render(target);
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

	SettingsText[Resolution].setString("Resolution");
	SettingsText[Fullscreen].setString("Fullscreen");
	SettingsText[FramerateLimit].setString("Framerate limit");
	SettingsText[VerticalSync].setString("Vertical sync");
	SettingsText[MusicVolume].setString("Music volume");
	SettingsText[SoundVolume].setString("Sound volume");

	SettingsList[Resolution] = new gui::DropDownList
	(
		SettingsText[Resolution].getPosition().x + (Container.getSize().x / 12.f * 4.f), SettingsText[Resolution].getPosition().y,
		gui::PercentToX(13.f, GfxSettings->Resolution), gui::PercentToY(4.0f, GfxSettings->Resolution),
		GfxSettings->Resolution, Font,
		VideoModeString.data(), static_cast<uint32>(VideoModeString.size())
	);
}
