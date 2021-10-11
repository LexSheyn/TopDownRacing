#include "../../stdafx.h"
#include "State.h"

// Constructors and Destructor:

State::State(StateData* stateData)
	: StData(stateData), StateLog(typeid(*this).name())
{
	GridSize = stateData->GridSize;

	Window = stateData->Window;

	SupportedKeys = stateData->SupportedKeys;

	SoundEngine = stateData->SoundEngine;

	States = stateData->States;

	Ended = false;

	Paused = false;

	InitFont(Font, "../Fonts/slkscr.ttf");

	InitMousePositionText();

	InitFpsCounter();

	InitKeyTime();
}

State::~State()
{

}


// Functions:

void State::EndState()
{
	Ended = true;
}

void State::PauseState()
{
	Paused = true;
}

void State::UnpauseState()
{
	Paused = false;
}

void State::UpdateMousePositions(sf::View* view)
{
	MousePositionScreen = sf::Mouse::getPosition();
	
	MousePositionWindow = sf::Mouse::getPosition(*Window);

	if (view)
	{
		Window->setView(*view);
	}

	MousePositionView = Window->mapPixelToCoords(sf::Mouse::getPosition(*Window));

	MousePositionGrid = sf::Vector2i
	(
		static_cast<int32>(MousePositionView.x / GridSize),
		static_cast<int32>(MousePositionView.y / GridSize)
	);

	Window->setView(Window->getDefaultView());
}

void State::UpdateSound(const float& dt)
{
	// To do..
}

void State::UpdteMousePositionText()
{
	// X position
	MousePositionTextX.setPosition(MousePositionView.x + 20.f, MousePositionView.y - 24.f);
	std::stringstream ssX;
	ssX << "x: " << MousePositionView.x;
	MousePositionTextX.setString(ssX.str());

	// Y position
	MousePositionTextY.setPosition(MousePositionView.x + 70.f, MousePositionView.y - 24.f);
	std::stringstream ssY;
	ssY << "y: " << MousePositionView.y;
	MousePositionTextY.setString(ssY.str());
}

void State::UpdateFpsCounter(const float& dt)
{
	FpsCounterText.setString("FPS: " + std::to_string(static_cast<int32>(1.f / dt)));
}

void State::RenderMousePositionText(sf::RenderTarget* target)
{
	target->draw(MousePositionTextX);
	target->draw(MousePositionTextY);
}

void State::RenderFpsCounter(sf::RenderTarget* target)
{
	target->draw(FpsCounterText);
}


// Accessors:

const bool& State::IsPaused() const
{
	return Paused;
}

const bool& State::IsEnded() const
{
	return Ended;
}

const bool State::GetKeyTime()
{
	if (KeyTimer.getElapsedTime().asSeconds() >= KeyTimeMax)
	{
		KeyTimer.restart();

		return true;
	}

	return false;
}

const bool State::GetKeyTime(const float& keyTimeMax)
{
	if (KeyTimer.getElapsedTime().asSeconds() >= keyTimeMax)
	{
		KeyTimer.restart();

		return true;
	}

	return false;
}


// Protected Functions:

bool State::InitKeybinds(const std::string& filePath)
{
	std::ifstream in;

	in.open(filePath);

	if (in.is_open())
	{
		std::string action = "";
		std::string key = "";

		while (in >> action >> key)
		{
			Keybinds[action] = SupportedKeys->at(key);
		}
	}
	else
	{
		StateLog.Error("InitKeybinds::Failed to open: " + filePath);

		return false;
	}

	in.close();

	StateLog.Trace("InitKeybinds::Keybinds initialized: " + filePath);

	return true;
}

bool State::InitFont(sf::Font& font, const std::string& filePath)
{
	if (!font.loadFromFile(filePath))
	{
		StateLog.Error("InitFont::Failed to load: " + filePath);

		return false;
	}

	StateLog.Trace("InitFont::Font initialized: " + filePath);

	return true;
}

bool State::InitTexture(sf::Texture& texture, const std::string& filePath)
{
	if (!texture.loadFromFile(filePath))
	{
		StateLog.Error("InitTexture::Failed to load: " + filePath);

		return false;
	}

	StateLog.Trace("InitTextures::Texture initialized: " + filePath);

	return true;
}

void State::InitKeyTime()
{
	// Key time in seconds
	KeyTimeMax = 0.3f;
	KeyTimer.restart();
}

void State::InitMousePositionText()
{
	//X
	MousePositionTextX.setFont(Font);
//	MousePositionTextX.setCharacterSize(gui::calculateCharSize(3.3f, this->stateData->gfxSettings->resolution));

	//Y
	MousePositionTextY.setFont(Font);
//	MousePositionTextY.setCharacterSize(gui::calculateCharSize(3.3f, this->stateData->gfxSettings->resolution));
}

void State::InitFpsCounter()
{
	FpsCounterText.setFont(Font);
	FpsCounterText.setCharacterSize(20);
//	FpsCounterText.setPosition
//	(
//
//	);
}
