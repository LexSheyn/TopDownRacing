#include "../stdafx.h"
#include "Resizers.h"

namespace gui
{
	const float PercentToX(const float percent, const sf::VideoMode& video_mode)
	{
		return std::floor(static_cast<float>(video_mode.width) * (percent / 100.f));
	}

	const float PercentToY(const float percent, const sf::VideoMode& video_mode)
	{
		return std::floor(static_cast<float>(video_mode.height) * (percent / 100.f));
	}

	const unsigned CalculateCharSize(const float percent, const sf::VideoMode& video_mode)
	{
		if (video_mode.width > video_mode.height)
		{
			return static_cast<uint32>(std::floor(static_cast<float>(video_mode.height) * (percent / 100.f)));
		}

		return static_cast<uint32>(std::floor(static_cast<float>(video_mode.width) * (percent / 100.f)));
	}
}