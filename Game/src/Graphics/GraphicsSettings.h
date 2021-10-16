#pragma once
class GraphicsSettings
{
public:

// Constructors and Destructor:

	GraphicsSettings();

	~GraphicsSettings();

// Functions:

	bool Save(const std::string& filePath);

	bool Load(const std::string& filePath);

// Variables:

	std::string Title;

	sf::VideoMode Resolution;

	int32 Fullscreen;

	uint32 Style;

	uint32 FramerateLimit;

	bool VerticalSync;

	sf::ContextSettings ContextSettings;

	bool CursorGrabbing;

	std::vector<sf::VideoMode> VideoModes;

private:

// Variables:

	Logger Log;
};

