#pragma once

#include "Base/EditorMode.h"
#include "../GUI/TextureSelector.h"

class MapEditorMode : public EditorMode
{
public:

// Constructors and Destructor:

	MapEditorMode(StateData* stateData, EditorStateData* editorStateData, TileMap* tileMap);

	~MapEditorMode();

// Functions:

	void UpdateInput(const float& dt) override;

	void UpdateGui(const float& dt) override;

	void Update(const float& dt) override;

	void RenderGui(sf::RenderTarget* target) override;

	void Render(sf::RenderTarget* target) override;

private:

// Private Functions:

	void InitVariables();

	void InitGui();

// Variables:

	sf::Text CursorText;
	sf::RectangleShape SideBar;
	sf::RectangleShape SelectorRect;
	gui::TextureSelector* TextureSelector;
	sf::IntRect TextureRect;
	bool Collision;
	int32 Layer;
	bool AddLocked;
};
