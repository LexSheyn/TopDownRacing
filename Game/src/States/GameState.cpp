#include "../stdafx.h"
#include "GameState.h"

GameState::GameState(StateData* stateData)
	: State(stateData), Log(typeid(*this).name()), 
	Menu(StData->GfxSettings->Resolution, Font), 
	MenuSettings(StData->Window, StData->GfxSettings, Font), 
	HpBar(10.f, 10.f, 200.f, 24.f)
{
	InitDefferedRenderer();

	InitView();

	State::InitKeybinds("../Config/gamestate_keybinds.ini");

	State::InitTexture(PlayerTexture, "../Resources/Images/Sprites/Player/ship.png");
	State::InitTexture(ButtonTextures[Resume], "../Resources/Images/GUI/Buttons/resume.png");
	State::InitTexture(ButtonTextures[Settings], "../Resources/Images/GUI/Buttons/settings.png");
	State::InitTexture(ButtonTextures[Exit], "../Resources/Images/GUI/Buttons/exit.png");

	InitTileMap();

	InitMenus();

	InitPlayers();

	InitPlayerGui();

	InitSystems();

	InitSound();
}

GameState::~GameState()
{
	delete Map;

	delete PlayerOne;
//
//	delete PlayerGui;
//
//	delete TextTagSystem;
}


// Functions:

void GameState::UpdateView(const float& dt)
{
	// Setting center default
	this->View.setCenter
	(
		std::floor(PlayerOne->GetPosition().x + (static_cast<float>(MousePositionWindow.x) - static_cast<float>(StData->GfxSettings->Resolution.width / 2)) / 10.f),
		std::floor(PlayerOne->GetPosition().y + (static_cast<float>(MousePositionWindow.y) - static_cast<float>(StData->GfxSettings->Resolution.height / 2)) / 10.f)
	);

	//Check for X
//	if (View.getSize().x <= Map->GetSizeF().x)
//	{
//		if (View.getCenter().x - (View.getSize().x / 2.f) < 0.f)
//		{
//			View.setCenter(0.f + (View.getSize().x / 2.f), View.getCenter().y);
//		}
//		else if (View.getCenter().x + (View.getSize().x / 2.f) > Map->GetSizeF().x)
//		{
//			View.setCenter(Map->GetSizeF().x - (View.getSize().x / 2.f), View.getCenter().y);
//		}
//	}
//
//	//Check for Y
//	if (View.getSize().y <= Map->GetSizeF().y)
//	{
//		if (View.getCenter().y - (View.getSize().y / 2.f) < 0.f)
//		{
//			View.setCenter(View.getCenter().x, 0.f + (View.getSize().y / 2.f));
//		}
//		else if (View.getCenter().y + (View.getSize().y / 2.f) > Map->GetSizeF().y)
//		{
//			View.setCenter(View.getCenter().x, Map->GetSizeF().y - (View.getSize().y / 2.f));
//		}
//	}

	// Setting rotation
	View.setRotation(PlayerOne->GetRotation());

	// ???
	ViewPositionGrid.x = static_cast<int32>(View.getCenter().x) / static_cast<int32>(StData->GridSize);
	ViewPositionGrid.y = static_cast<int32>(View.getCenter().y) / static_cast<int32>(StData->GridSize);
}

void GameState::UpdateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(Keybinds.at("CLOSE"))) && GetKeyTime())
	{
		if (!State::IsPaused())
		{
			State::PauseState();
		}
		else if (MenuSettings.IsOpen())
		{
			MenuSettings.Close();			
		}
		else
		{
			State::UnpauseState();
		}
	}
}

void GameState::UpdatePlayerInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
	//	SoundEngine->PlaySound(sfx::Sound::Covered);

		PlayerOne->Drive(dt);
		PlayerOne->GainHp(1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		PlayerOne->Reverse(dt);
		PlayerOne->LoseHp(1);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		PlayerOne->TurnLeft(dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		PlayerOne->TurnRight(dt);
	}
}

void GameState::UpdatePlayerGui(const float& dt)
{
	HpBar.Update
	(
		static_cast<int32>(std::sqrt(std::pow(PlayerOne->GetEngineComponent()->GetVelocity().x, 2) + std::pow(PlayerOne->GetEngineComponent()->GetVelocity().y, 2)) * dt),
		10,
		dt
	);
}

void GameState::UpdateMenus(const sf::Vector2i& mousePosition, const float& dt)
{
	Menu.Update(mousePosition, dt);

	if (Menu.IsButtonPressed(Resume) && GetKeyTime())
	{
		SoundEngine->PlaySound(sfx::Sound::Positive);
		State::UnpauseState();
	}
	else if (Menu.IsButtonPressed(Settings) && GetKeyTime())
	{
		SoundEngine->PlaySound(sfx::Sound::Positive);
		
		if (!MenuSettings.IsOpen())
		{
			MenuSettings.Open();
		}
		else
		{
			MenuSettings.Close();
		}
	}
	else if (Menu.IsButtonPressed(Exit) && GetKeyTime())
	{
		SoundEngine->PlaySound(sfx::Sound::Negative);
		State::EndState();
	}

	MenuSettings.Update(mousePosition, dt);
}

void GameState::UpdateTileMap(const float& dt)
{
	Map->UpdateMapBoundsCollision(PlayerOne, dt);
	Map->UpdateTileCollision(PlayerOne, dt);
}

void GameState::UpdatePlayer(const float& dt)
{
	PlayerOne->Update(dt, MousePositionView);
}

void GameState::Update(const float& dt)
{
	State::UpdateMousePositions(&View);

	UpdateInput(dt);

	if (!State::IsPaused())
	{
		UpdateView(dt);		

		UpdatePlayerInput(dt);

		UpdatePlayer(dt);

		UpdateTileMap(dt);

		UpdatePlayerGui(dt);
	}
	else
	{
		UpdateMenus(MousePositionWindow, dt);
	}

	State::UpdateSound();
}

void GameState::Render(sf::RenderTarget* target)
{
	RenderTexture.clear();

	RenderTexture.setView(View);

	Map->Render(&RenderTexture, ViewPositionGrid, false);

	PlayerOne->Render(&RenderTexture, false);

	// Pause menu
	if (State::IsPaused())
	{
		RenderTexture.setView(Window->getDefaultView());
		Menu.Render(&RenderTexture);
		MenuSettings.Render(&RenderTexture);
	}

	RenderTexture.setView(Window->getDefaultView());
	HpBar.Render(&RenderTexture);

	RenderTexture.display();

	RenderTexture.setView(RenderTexture.getDefaultView());

	RenderSprite.setTexture(RenderTexture.getTexture());

	target->draw(RenderSprite);
}


// Private Functions:

void GameState::InitDefferedRenderer()
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

void GameState::InitView()
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

void GameState::InitTileMap()
{
	Map = new TileMap("../Maps/map.tilemap");
}

void GameState::InitMenus()
{
	Menu.AddButton(Resume, 0, &ButtonTextures[Resume]);
	Menu.AddButton(Settings, 2, &ButtonTextures[Settings]);
	Menu.AddButton(Exit, 4, &ButtonTextures[Exit]);
}

void GameState::InitPlayers()
{
	PlayerOne = new Player(PlayerTexture, 500.f, 500.f);
}

void GameState::InitPlayerGui()
{
	HpBar.SetFont(Font);
}

void GameState::InitSystems()
{
}

void GameState::InitSound()
{
	
}
