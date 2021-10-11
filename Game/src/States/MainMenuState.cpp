#include "../stdafx.h"
#include "MainMenuState.h"

// Constructors and Destructor:

MainMenuState::MainMenuState(StateData* stateData)
	: State(stateData), Log(typeid(*this).name())
{
	InitVariables();

	State::InitKeybinds("../Config/mainmenustate_keybinds.ini");

	State::InitTexture(ButtonTextures[Start], "../Resources/Images/GUI/Buttons/start.png");
	State::InitTexture(ButtonTextures[Exit], "../Resources/Images/GUI/Buttons/exit.png");

	InitGui();

	// VFX
	// To do...

	// Music and SFX
	InitSound();

	Log.Trace("Main menu initialized");
}

MainMenuState::~MainMenuState()
{
	// Deleting buttons
	for (auto& button : Buttons)
	{
		delete button.second;
	}

	Buttons.clear();
}


// Functions:

void MainMenuState::UpdateInput(const float& dt)
{
	if (Buttons[Start]->IsPressed() && State::GetKeyTime())
	{
		SoundEngine->PlaySound(sfx::Sound::Positive);
		States->push(new GameState(StData));
	}
	else if (Buttons[Exit]->IsPressed() && State::GetKeyTime())
	{
		SoundEngine->PlaySound(sfx::Sound::Negative);
		State::EndState();
	}
}

void MainMenuState::UpdateButtons(const float& dt)
{
	for (auto& button : Buttons)
	{
		button.second->Update(MousePositionWindow, dt);
	}
}

void MainMenuState::Update(const float& dt)
{
	State::UpdateMousePositions();

	UpdateButtons(dt);

	UpdateInput(dt);

	// FPS counter
	State::UpdateFpsCounter(dt);

	// Music and SFX
	State::UpdateSound();
}

void MainMenuState::RenderButtons(sf::RenderTarget* target)
{
	for (auto& button : Buttons)
	{
		button.second->Render(target);
	}
}

void MainMenuState::Render(sf::RenderTarget* target)
{
	target->draw(Background);

	target->draw(Container);

	RenderButtons(target);

	// To do...

	State::RenderMousePositionText(target);

	State::RenderFpsCounter(target);
}


// Private Functions:

void MainMenuState::InitVariables()
{
	// To do...
}

void MainMenuState::InitBackground(const std::string& filePath)
{
	sf::VideoMode vm = StData->GfxSettings->Resolution;

	Background.setSize
	(
		sf::Vector2f
		(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);
	
	if (State::InitTexture(BackgroundTexture, filePath))
	{
		Background.setTexture(&BackgroundTexture);

		Log.Trace("InitBackground::Background initialized: " + filePath);
	}
	else
	{
		Background.setFillColor(sf::Color());

		Log.Error("InitBackground::Failed to load: " + filePath);
	}
}

void MainMenuState::InitGui()
{
	const sf::VideoMode& vm = StData->GfxSettings->Resolution;

	// Background
	InitBackground("../Resources/Images/Backgrounds/test.png"); // To do...

	// Buttons
	Buttons[Start] = new gui::Button
	(
		gui::PercentToX(43.8f, vm), gui::PercentToY(70.f, vm),
		static_cast<float>(StData->GfxSettings->Resolution.width) / 9.f,
		static_cast<float>(StData->GfxSettings->Resolution.height) / 24.f,
		0u, &ButtonTextures[Start]
	);

	Buttons[Exit] = new gui::Button
	(
		gui::PercentToX(43.8f, vm), gui::PercentToY(78.f, vm),
		static_cast<float>(StData->GfxSettings->Resolution.width) / 9.f,
		static_cast<float>(StData->GfxSettings->Resolution.height) / 24.f,
		1u, &ButtonTextures[Exit]
	);
}

void MainMenuState::InitSound()
{
	SoundEngine->InitSound(sfx::Sound::Positive, "../Resources/Sounds/Buttons/positive.mp3");
	SoundEngine->InitSound(sfx::Sound::Covered, "../Resources/Sounds/Buttons/covered.mp3");
	SoundEngine->InitSound(sfx::Sound::Negative, "../Resources/Sounds/Buttons/negative.mp3");
}

void MainMenuState::ResetGui()
{
	for (auto& button : Buttons)
	{
		delete button.second;
	}

	InitGui();
}
