#pragma once

#include "Base/State.h"
#include "../Menus/PauseMenu.h"
#include "../Map/TileMap.h"
#include "../EditorModes/MapEditorMode.h"

class EditorState : public State
{
public:

// Modes:

	enum class Mode : uint32
	{
		Tiles = 0, Entities
	};

// Constructors and Destructor:

	EditorState(StateData* stateData);

	~EditorState();

// Functions:

	// Pure virtual
	void ResetGui() override {}

	void ZoomIn(const float& dt);

	void ZoomOut(const float& dt);

	void ZoomReset();

	void UpdateView(const float& dt);

	void UpdateInput(const float& dt) override;

	void UpdateEditorInput(const float& dt);

	void UpdateButtons(const float& dt);

	void UpdateGui(const float& dt);

	void UpdatePauseMenu(const sf::Vector2i& mousePosition, const float& dt);

	void UpdateModes(const float& dt);

	void Update(const float& dt) override;

	void RenderButtons(sf::RenderTarget* target);

	void RenderGui(sf::RenderTarget* target);

	void RenderModes(sf::RenderTarget* target);

	void Render(sf::RenderTarget* target) override;

private:

// Private Functions:

	void InitVariables();

	void InitEditorStateData();

	void InitDefferedRenderer();

	void InitView();

	void InitPauseMenu();

	void InitButtons();

	void InitGui();

	void InitTileMap();

	void InitModes();

	void InitSound() override;

// Variables:

	EditorStateData EditorData;

	sf::View View;
	sf::Vector2i ViewPositionGrid;
	float ViewSpeed;
	float ViewScaleMax;
	float ViewScaleMin;
	float ViewScale;
	sf::RenderTexture RenderTexture;
	sf::Sprite RenderSprite;

	PauseMenu Menu;

	enum EditorButton : int32
	{
		Resume = 0, Save, Load, Settings, Exit
	};

	std::map<const EditorButton, gui::Button*> Buttons;

	TileMap* Map;

	std::vector<EditorMode*> Modes;
	uint32 ActiveMode;
};