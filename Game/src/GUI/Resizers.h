#pragma once

namespace gui
{
	//Converts a percentage value to pixels relative to current resolution in the X axis.
	//@param	float percent			The percentage value.
	//@param	sf::VideoMode& video_mode	Current video mode of the window (resolution).
	//@return	float				The calculated pixel value.
	const float PercentToX(const float percent, const sf::VideoMode& video_mode);

	//Converts a percentage value to pixels relative to current resolution in the Y axis.
	//@param	float percent			The percentage value.
	//@param	sf::VideoMode& video_mode	Current video mode of the window (resolution).
	//@return	float				The calculated pixel value.
	const float PercentToY(const float percent, const sf::VideoMode& video_mode);

	//Calculates the character size for text using the current resolution and a constant.
	//@param	float percent			The percentage value.
	//@param	sf::VideoMode& video_mode	Current video mode of the window (resolution).
	//@return	unsigned			The calculated character size value.
	const unsigned CalculateCharSize(const float percent, const sf::VideoMode& video_mode);
}