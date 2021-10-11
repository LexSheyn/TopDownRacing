#include "../stdafx.h"
#include "EditorState.h"

// Constructors and Destructors:

EditorState::EditorState(StateData* stateData)
	: State(stateData), Menu(StData->GfxSettings->Resolution, Font)
{
	InitVariables();

	InitEditorStateData();

	InitDefferedRenderer();

	InitView();

	State::InitKeybinds("../Config/editorstate_keybinds.ini");

	State::InitTexture(ButtonTextures[Resume], "../Resources/Images/GUI/Buttons/resume.png");
	State::InitTexture(ButtonTextures[Save], "../Resources/Images/GUI/Buttons/save.png");
	State::InitTexture(ButtonTextures[Load], "../Resources/Images/GUI/Buttons/load.png");
	State::InitTexture(ButtonTextures[Settings], "../Resources/Images/GUI/Buttons/settings.png");
	State::InitTexture(ButtonTextures[Exit], "../Resources/Images/GUI/Buttons/exit.png");

	InitPauseMenu();

	InitButtons();

	InitTileMap();

	InitGui();

	InitModes();

	InitSound();
}

EditorState::~EditorState()
{
	// Deleting buttons
	for (auto& button : Buttons)
	{
		delete button.second;
	}

	Buttons.clear();

	// Deleting pause menu
	//

	// Deleting editor modes
	for (auto& mode : Modes)
	{
		delete mode;
	}

	Modes.clear();

	// Deleting map
	delete Map;
}


// Functions:

void EditorState::ZoomIn(const float& dt)
{
	ViewScale += dt;

	if (ViewScale > ViewScaleMax)
	{
		ViewScale = ViewScaleMax;
	}

	View.setSize
	(
		sf::Vector2f
		(
			static_cast<float>(StData->GfxSettings->Resolution.width) * ViewScale,
			static_cast<float>(StData->GfxSettings->Resolution.height) * ViewScale
		)
	);
}

void EditorState::ZoomOut(const float& dt)
{
	ViewScale -= dt;

	if (ViewScale < ViewScaleMin)
	{
		ViewScale = ViewScaleMin;
	}

	View.setSize
	(
		sf::Vector2f
		(
			static_cast<float>(StData->GfxSettings->Resolution.width) * ViewScale,
			static_cast<float>(StData->GfxSettings->Resolution.height) * ViewScale
		)
	);
}

void EditorState::ZoomReset()
{
	ViewScale = 1.f;

	View.setSize
	(
		sf::Vector2f
		(
			static_cast<float>(StData->GfxSettings->Resolution.width),
			static_cast<float>(StData->GfxSettings->Resolution.height)
		)
	);
}

void EditorState::UpdateView(const float& dt)
{
	ViewPositionGrid.x = static_cast<int32>(View.getCenter().x / StData->GridSize);
	ViewPositionGrid.y = static_cast<int32>(View.getCenter().y / StData->GridSize);
}

void EditorState::UpdateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(Keybinds.at("CLOSE"))) && GetKeyTime())
	{
		if (!State::IsPaused())
		{
			State::PauseState();
		}
		else
		{
			State::UnpauseState();
		}
	}
}

void EditorState::UpdateEditorInput(const float& dt)
{
	//Moving view
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(Keybinds.at("CAMERA_MOVE_UP"))))
	{
		View.move(0.f, -std::ceil(ViewSpeed * dt));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(Keybinds.at("CAMERA_MOVE_DOWN"))))
	{
		View.move(0.f, std::ceil(ViewSpeed * dt));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(Keybinds.at("CAMERA_MOVE_LEFT"))))
	{
		View.move(-std::ceil(ViewSpeed * dt), 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(Keybinds.at("CAMERA_MOVE_RIGHT"))))
	{
		View.move(std::ceil(ViewSpeed * dt), 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(Keybinds.at("MODE_UP"))) && GetKeyTime())
	{
		if (ActiveMode < static_cast<uint32>(Modes.size() - 1u))
		{
			ActiveMode++;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(Keybinds.at("MODE_DOWN"))) && GetKeyTime())
	{
		if (ActiveMode > 0)
		{
			ActiveMode--;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(Keybinds.at("ZOOM_IN"))))
	{
		ZoomIn(dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(Keybinds.at("ZOOM_OUT"))))
	{
		ZoomOut(dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(Keybinds.at("ZOOM_RESET"))))
	{
		ZoomReset();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(Keybinds.at("CLOSE"))) && GetKeyTime())
	{
		if (!State::IsPaused())
		{
			State::PauseState();
		}
		else
		{
			State::UnpauseState();
		}
	}
}

void EditorState::UpdateButtons(const float& dt)
{
	for (auto& button : Buttons)
	{
		button.second->Update(MousePositionWindow, dt);
	}
}

void EditorState::UpdateGui(const float& dt)
{
	//
}

void EditorState::UpdatePauseMenu(const sf::Vector2i& mousePosition, const float& dt)
{
	Menu.Update(mousePosition, dt);

	if (Menu.IsButtonPressed(Resume) && GetKeyTime())
	{
		State::UnpauseState();
	}
	else if (Menu.IsButtonPressed(Save) && GetKeyTime())
	{
		Map->Save("../Maps/map.tilemap");
	}
	else if (Menu.IsButtonPressed(Load) && GetKeyTime())
	{
		Map->Load("../Maps/map.tilemap");
	}
	else if (Menu.IsButtonPressed(Settings) && GetKeyTime())
	{
		//
	}
	else if (Menu.IsButtonPressed(Exit) && GetKeyTime())
	{
		State::EndState();
	}
}

void EditorState::UpdateModes(const float& dt)
{
	Modes[ActiveMode]->Update(dt);
}

void EditorState::Update(const float& dt)
{
	State::UpdateMousePositions(&View);

	UpdateInput(dt);

	if (!State::IsPaused())
	{
		UpdateView(dt);

		UpdateButtons(dt);

		UpdateGui(dt);

		UpdateEditorInput(dt);

		UpdateModes(dt);
	}
	else
	{
		UpdatePauseMenu(MousePositionWindow, dt);
	}
}

void EditorState::RenderButtons(sf::RenderTarget* target)
{
	for (auto& button : Buttons)
	{
		button.second->Render(target);
	}
}

void EditorState::RenderGui(sf::RenderTarget* target)
{
	//
}

void EditorState::RenderModes(sf::RenderTarget* target)
{
	Modes[ActiveMode]->Render(target);
}

void EditorState::Render(sf::RenderTarget* target)
{
	RenderTexture.clear();

	// Map
	RenderTexture.setView(View);
	Map->Render(&RenderTexture, ViewPositionGrid, true);

	// GUI
	RenderTexture.setView(Window->getDefaultView());
	RenderButtons(&RenderTexture);
	RenderGui(&RenderTexture);
	RenderModes(&RenderTexture);

	// Pause menu
	if (State::IsPaused())
	{
		RenderTexture.setView(Window->getDefaultView());
		Menu.Render(&RenderTexture);
	}

	RenderTexture.display();

	RenderTexture.setView(RenderTexture.getDefaultView());

	RenderSprite.setTexture(RenderTexture.getTexture());

	target->draw(RenderSprite);
}


// Private Functions:

void EditorState::InitVariables()
{
	ViewSpeed = 1000.f;
	ViewScaleMax = 2.f;
	ViewScaleMin = 0.5f;
	ViewScale = 1.f;
}

void EditorState::InitEditorStateData()
{
	EditorData.View = &View;
	
	EditorData.Font = &Font;

	EditorData.Keybinds = &Keybinds;
	
	EditorData.KeyTimer = &KeyTimer;
	EditorData.KeyTimeMax = &KeyTimeMax;
	
	EditorData.MousePositionScreen = &MousePositionScreen;
	EditorData.MousePositionWindow = &MousePositionWindow;
	EditorData.MousePositionView = &MousePositionView;
	EditorData.MousePositionGrid = &MousePositionGrid;
}

void EditorState::InitDefferedRenderer()
{
	RenderTexture.create
	(
		StData->GfxSettings->Resolution.width,
		StData->GfxSettings->Resolution.height
	);

	RenderSprite.setTexture(RenderTexture.getTexture());
	RenderSprite.setTextureRect
	(
		sf::IntRect
		(
			0,
			0,
			StData->GfxSettings->Resolution.width,
			StData->GfxSettings->Resolution.height
		)
	);
}

void EditorState::InitView()
{
	View.setSize
	(
		sf::Vector2f
		(
			static_cast<float>(StData->GfxSettings->Resolution.width),
			static_cast<float>(StData->GfxSettings->Resolution.height)
		)
	);

	View.setCenter
	(
		static_cast<float>(StData->GfxSettings->Resolution.width) / 2.f,
		static_cast<float>(StData->GfxSettings->Resolution.height) / 2.f
	);
}

void EditorState::InitPauseMenu()
{
	Menu.AddButton(Resume, 0, &ButtonTextures[Resume]);
	Menu.AddButton(Save, 1, &ButtonTextures[Save]);
	Menu.AddButton(Load, 2, &ButtonTextures[Load]);
	Menu.AddButton(Settings, 3, &ButtonTextures[Settings]);
	Menu.AddButton(Exit, 5, &ButtonTextures[Exit]);
}

void EditorState::InitButtons()
{
	//
}

void EditorState::InitGui()
{
	//
}

void EditorState::InitTileMap()
{
	Map = new TileMap(StData->GridSize, 32, 32, 1, "../Resources/Images/Tiles/tilesheet_256_64.png");
}

void EditorState::InitModes()
{
	Modes.push_back(new MapEditorMode(StData, &EditorData, Map));

	ActiveMode = static_cast<uint32>(EditorState::Mode::Tiles);
}

void EditorState::InitSound()
{

}
