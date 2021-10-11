#include "../stdafx.h"
#include "Game.h"

// Constructors and Destructor:

Game::Game()
	: Log(typeid(*this).name())
{
	InitVariables();

	InitGraphicsSettings("../Config/graphics.ini");

	InitWindow();

	InitKeys("../Config/supported_keys.ini");

	InitStateData();

	InitStates();

	InitFadeScreen();
}

Game::~Game()
{
	// Deleting SFML window
	delete Window;

	// Deleting states
	while (!States.empty())
	{
		delete States.top();
		States.pop();
	}
}


// Functions:

void Game::Run()
{
	while (Window->isOpen())
	{
		UpdateEvents();

		UpdateDt();

		if (Window->hasFocus())
		{
			Update();
		}

		Render();
	}
}

void Game::UpdateDt()
{
	Dt = DtClock.restart().asSeconds();
}

void Game::UpdateEvents()
{
	while (Window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
		{
			Window->close();
		}
	}
}

void Game::Update()
{
	if (!States.empty())
	{
		States.top()->Update(Dt);

		if (States.top()->IsEnded())
		{
			States.top()->EndState();
			delete States.top();
			States.pop();
		}
	}
	else
	{
		Window->close();
	}
}

void Game::Render()
{
	// Clearing frame with black color by default
	Window->clear();

	// Rendering active state
	if (!States.empty())
	{
		States.top()->Render(Window);
	}

	// Displaying frame
	Window->display();
}


// Private Functions:

void Game::InitVariables()
{
	Window = nullptr;

	Dt = 0.f;

	GridSize = 64.f;
}

bool Game::InitGraphicsSettings(const std::string& filePath)
{
	if (!GfxSettings.Load(filePath))
	{
		Log.Error("InitGraphicsSettings::Failed to load: " + filePath);

		return false;
	}

	Log.Trace("InitGraphicsSettings::Settings initialized: " + filePath);

	return true;
}

void Game::InitWindow()
{
	Window = new sf::RenderWindow
	(
		GfxSettings.Resolution,
		GfxSettings.Title,
		GfxSettings.Style,
		GfxSettings.ContextSettings
	);

	Window->setFramerateLimit(GfxSettings.FrameRateLimit);
	Window->setVerticalSyncEnabled(GfxSettings.VerticalSync);
	Window->setMouseCursorGrabbed(GfxSettings.CursorGrabbing);
}

bool Game::InitKeys(const std::string& filePath)
{
	std::ifstream in;

	in.open(filePath);

	if (in.is_open())
	{
		std::string key = "";
		int32 keyValue = 0;

		while (in >> key >> keyValue)
		{
			SupportedKeys[key] = keyValue;
		}
	}
	else
	{
		Log.Error("InitKeys::Failed to open: " + filePath);

		return false;
	}

	in.close();

	Log.Trace("InitKeys::Supported keys:");

	for (auto& keys : SupportedKeys)
	{
		std::cout << keys.first << " " << keys.second << std::endl;
	}

	Log.Trace("InitKeys::Keys loaded: " + filePath);

	return true;
}

void Game::InitStateData()
{
	StData.GridSize = GridSize;

	StData.Window = Window;

	StData.GfxSettings = &GfxSettings;

	StData.SupportedKeys = &SupportedKeys;

	StData.SoundEngine = &SoundEngine;

	StData.States = &States;
}

void Game::InitFadeScreen()
{
	//
}

void Game::InitStates()
{
	// Main menu
	States.push(new MainMenuState(&StData));
}