#pragma once

#include "../../States/Base/State.h"
#include "../../Map/TileMap.h"

class EditorStateData;

class EditorMode
{
public:

// Constructors and Destructor:

	EditorMode(StateData* stateData, EditorStateData* editorStateData, TileMap* tileMap);

	virtual ~EditorMode();

// Functions:

	virtual void UpdateInput(const float& dt) = 0;

	virtual void UpdateGui(const float& dt) = 0;

	virtual void Update(const float& dt) = 0;

	virtual void RenderGui(sf::RenderTarget* target) = 0;

	virtual void Render(sf::RenderTarget* target) = 0;

// Accessors:

	const bool GetKeyTime();

	const bool GetKeyTime(const float keyTimeMax);

protected:

	StateData* StData;
	EditorStateData* EditorData;
	TileMap* Map;
};

class EditorStateData
{
public:

// Variables:

	sf::View* View;

	sf::Font* Font;

	std::map<const std::string, int32>* Keybinds;

	sf::Clock* KeyTimer;
	float* KeyTimeMax;

	sf::Vector2i* MousePositionScreen;
	sf::Vector2i* MousePositionWindow;
	sf::Vector2f* MousePositionView;
	sf::Vector2i* MousePositionGrid;
};
