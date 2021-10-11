#include "../stdafx.h"
#include "GraphicsSettings.h"

// Constructors and Destructor:

GraphicsSettings::GraphicsSettings()
	: Log(typeid(*this).name())
{
	Title = "Title";

	Resolution = sf::VideoMode::getDesktopMode();

	Fullscreen = 0;

	Style = sf::Style::Titlebar | sf::Style::Close;

	FrameRateLimit = 30;

	VerticalSync = false;

	ContextSettings.antialiasingLevel = 0;

	CursorGrabbing = false;

	VideoModes = sf::VideoMode::getFullscreenModes();

	Log.Trace("Default settings initialized");
}

GraphicsSettings::~GraphicsSettings()
{
	//
}

// Functions:

bool GraphicsSettings::Save(const std::string& filePath)
{
	std::ofstream out;

	out.open(filePath);

	if (out.is_open())
	{
		out << Title << std::endl;
		out << Resolution.width << " " << Resolution.height << std::endl;
		out << Fullscreen << std::endl;
		out << FrameRateLimit << std::endl;
		out << VerticalSync << std::endl;
		out << ContextSettings.antialiasingLevel << std::endl;
		out << CursorGrabbing << std::endl;
	}
	else
	{
		Log.Error("Save::Failed to open " + filePath);

		return false;
	}

	out.close();

	Log.Trace("Save::Settings saved: " + filePath);

	return true;
}

bool GraphicsSettings::Load(const std::string& filePath)
{
	std::ifstream in;

	in.open(filePath);

	if (in.is_open())
	{
		std::getline(in, Title);
		in >> Resolution.width >> Resolution.height;
		in >> Fullscreen;
		in >> FrameRateLimit;
		in >> VerticalSync;
		in >> ContextSettings.antialiasingLevel;
		in >> CursorGrabbing;
	}
	else
	{
		Log.Error("Load::Failed to open " + filePath);

		return false;
	}

	in.close();

	// Fullscreen
	if (Fullscreen == 0)
	{
		Style = sf::Style::Titlebar | sf::Style::Close;
	}
	else if (Fullscreen == 1)
	{
		Style = sf::Style::Fullscreen;
	}
	else if (Fullscreen == 2)
	{
		Style = sf::Style::None;
	}
	else
	{
		Style = sf::Style::Default;
	}

	Log.Trace("Load::Setting loaded: " + filePath);

	return true;
}