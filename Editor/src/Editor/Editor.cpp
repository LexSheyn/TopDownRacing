#include "../stdafx.h"
#include "Editor.h"

// Constructors and Destructor:

Editor::Editor()
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

Editor::~Editor()
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

void Editor::Run()
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

void Editor::UpdateDt()
{
	Dt = DtClock.restart().asSeconds();
}

void Editor::UpdateEvents()
{
	while (Window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
		{
			Window->close();
		}
	}
}

void Editor::Update()
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

void Editor::Render()
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

void Editor::InitVariables()
{
	Window = nullptr;

	Dt = 0.f;

	GridSize = 64.f;
}

bool Editor::InitGraphicsSettings(const std::string& filePath)
{
	if (!GfxSettings.Load(filePath))
	{
		Log.Error("InitGraphicsSettings::Failed to load: " + filePath);

		return false;
	}

	Log.Trace("InitGraphicsSettings::Settings loaded: " + filePath);

	return true;
}

void Editor::InitWindow()
{
	Window = new sf::RenderWindow
	(
		GfxSettings.Resolution,
		GfxSettings.Title,
		GfxSettings.Style,
		GfxSettings.ContextSettings
	);

	Window->setFramerateLimit(GfxSettings.FramerateLimit);
	Window->setVerticalSyncEnabled(GfxSettings.VerticalSync);
	Window->setMouseCursorGrabbed(GfxSettings.CursorGrabbing);
}

bool Editor::InitKeys(const std::string& filePath)
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

void Editor::InitStateData()
{
	StData.GridSize = GridSize;

	StData.Window = Window;

	StData.GfxSettings = &GfxSettings;

	StData.SupportedKeys = &SupportedKeys;

	StData.SoundEngine = &SoundEngine;

	StData.States = &States;
}

void Editor::InitFadeScreen()
{
	//
}

void Editor::InitStates()
{
	// Main menu
	States.push(new EditorState(&StData));
}