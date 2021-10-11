#pragma once

#include "../States/EditorState.h"

class Editor
{
public:

// Constructors and Destructor:

	Editor();

	~Editor();

// Functions:

	void Run();

	void UpdateDt();

	void UpdateEvents();

	void Update();

	void Render();

private:

// Private Functions:

	void InitVariables();

	bool InitGraphicsSettings(const std::string& filePath);

	void InitWindow();

	bool InitKeys(const std::string& filePath);

	void InitStateData();

	void InitFadeScreen();

	void InitStates();	

// Variables:

	// Logger
	Logger Log;

	// Map grid size
	float GridSize;

	// Core
	StateData StData;
	sf::RenderWindow* Window;
	GraphicsSettings GfxSettings;
	sf::Event Event;

	// Keys
	std::map<const std::string, int32> SupportedKeys;

	// Sound
	sfx::SoundEngine SoundEngine;

	// States
	std::stack<State*> States;

	// Delta time
	sf::Clock DtClock;
	float Dt;
};