#pragma once

#include "Base/State.h"
#include "../Menus/PauseMenu.h"
#include "../Menus/SettingsMenu.h"
#include "../Map/TileMap.h"
#include "../GUI/ProgressBar.h"

class GameState : public State
{
public:

// Constructors and Destructors:

	GameState(StateData* stateData);

	~GameState();

// Functions:

	void UpdateView(const float& dt);

	void UpdateInput(const float& dt) override;

	void UpdatePlayerInput(const float& dt);

	void UpdatePlayerGui(const float& dt);

	void UpdateMenus(const sf::Vector2i& mousePosition, const float& dt);

	void UpdateTileMap(const float& dt);

	void UpdatePlayer(const float& dt);

	void Update(const float& dt) override;

	void Render(sf::RenderTarget* target) override;

private:

// Private Functions:

	void InitDefferedRenderer();

	void InitView();

	void InitTileMap();

	void InitMenus();

	void InitPlayers();

	void InitPlayerGui();

	void InitSystems();

	void InitSound() override;

// Variables:

	// Logger
	Logger Log;

	sf::View View;
	sf::Vector2i ViewPositionGrid;
	sf::RenderTexture RenderTexture;
	sf::Sprite RenderSprite;

	PauseMenu Menu;

	SettingsMenu MenuSettings;

	gui::ProgressBar HpBar;

	enum GameButton : int32
	{
		Resume = 0, Settings, Exit
	};

	TileMap* Map;

	Player* PlayerOne;
};

