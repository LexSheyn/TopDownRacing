#include "../../stdafx.h"
#include "EditorMode.h"

// Constructors and Destructor:

EditorMode::EditorMode(StateData* stateData, EditorStateData* editorStateData, TileMap* tileMap)
	: StData(stateData), EditorData(editorStateData), Map(tileMap)
{
}

EditorMode::~EditorMode()
{
}


// Functions:

const bool EditorMode::GetKeyTime()
{
	if (EditorData->KeyTimer->getElapsedTime().asSeconds() >= *EditorData->KeyTimeMax)
	{
		EditorData->KeyTimer->restart();

		return true;
	}

	return false;
}

const bool EditorMode::GetKeyTime(const float keyTimeMax)
{
	if (EditorData->KeyTimer->getElapsedTime().asSeconds() >= keyTimeMax)
	{
		EditorData->KeyTimer->restart();

		return true;
	}

	return false;
}
