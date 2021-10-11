#include "../stdafx.h"
#include "MapEditorMode.h"

// Constructors and Destructor:

MapEditorMode::MapEditorMode(StateData* stateData, EditorStateData* editorStateData, TileMap* tileMap)
	: EditorMode(stateData, editorStateData, tileMap)
{
	InitVariables();

	InitGui();
}

MapEditorMode::~MapEditorMode()
{
	// Deleting texture selector
	delete TextureSelector;
}


// Functions:

void MapEditorMode::UpdateInput(const float& dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && GetKeyTime(0.05))
	{
		if (!SideBar.getGlobalBounds().contains(sf::Vector2f(*EditorData->MousePositionWindow)))
		{
			if (!TextureSelector->IsActive())
			{
				if (AddLocked)
				{
					if (Map->SectionEmpty(EditorData->MousePositionGrid->x, EditorData->MousePositionGrid->y, Map->GetLayer()))
					{
						Map->AddTile(EditorData->MousePositionGrid->x, EditorData->MousePositionGrid->y, Map->GetLayer(), TextureRect, Collision);
					}
				}
				else
				{
					Map->AddTile(EditorData->MousePositionGrid->x, EditorData->MousePositionGrid->y, Map->GetLayer(), TextureRect, Collision);
				}
			}
			else
			{
				TextureRect = TextureSelector->GetTextureRect();
			}
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && GetKeyTime(0.05))
	{
		if (!SideBar.getGlobalBounds().contains(sf::Vector2f(*EditorData->MousePositionWindow)))
		{
			if (!TextureSelector->IsActive())
			{
				Map->RemoveTile(EditorData->MousePositionGrid->x, EditorData->MousePositionGrid->y, Map->GetLayer());
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(EditorData->Keybinds->at("COLLISION_TOGGLE"))) && GetKeyTime())
	{
		if (Collision)
		{
			Collision = false;
		}
		else
		{
			Collision = true;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(EditorData->Keybinds->at("TILE_LOCK_TOGGLE"))) && GetKeyTime())
	{
		if (AddLocked)
		{
			AddLocked = false;
		}
		else
		{
			AddLocked = true;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(EditorData->Keybinds->at("TEXTURE_SELECTOR_TOGGLE"))) && GetKeyTime())
	{
		if (TextureSelector->IsVisible())
		{
			TextureSelector->Hide();
		}
		else
		{
			TextureSelector->Show();
		}
	}
}

void MapEditorMode::UpdateGui(const float& dt)
{
	// Texture selector
	TextureSelector->Update(*EditorData->MousePositionWindow, dt);

	// Tile selector
	if (!TextureSelector->IsActive())
	{
		SelectorRect.setTextureRect(TextureRect);
		SelectorRect.setPosition
		(
			EditorData->MousePositionGrid->x * StData->GridSize,
			EditorData->MousePositionGrid->y * StData->GridSize
		);
	}

	// Cursor text
	CursorText.setPosition
	(
		static_cast<float>(EditorData->MousePositionWindow->x) + 100.f,
		static_cast<float>(EditorData->MousePositionWindow->y) - 100.f
	);

	std::stringstream ss;
	ss << EditorData->MousePositionView->x << "    " << EditorData->MousePositionView->y
		<< std::endl << EditorData->MousePositionGrid->x << "    " << EditorData->MousePositionGrid->y
		<< std::endl << TextureRect.left << "    " << TextureRect.top
		<< std::endl << "Tiles: " << Map->GetLayerSize(EditorData->MousePositionGrid->x, EditorData->MousePositionGrid->y, Layer)
		<< std::endl << "Collision: " << Collision
		<< std::endl << "Lock: " << AddLocked;

	CursorText.setString(ss.str());
}

void MapEditorMode::Update(const float& dt)
{
	UpdateInput(dt);
	
	UpdateGui(dt);
}

void MapEditorMode::RenderGui(sf::RenderTarget* target)
{
// Editor data view:

	// Tile selector
	if (!TextureSelector->IsActive())
	{
		target->setView(*EditorData->View);
		target->draw(SelectorRect);
	}

// Window default view:

	// Texture selector
	target->setView(StData->Window->getDefaultView());
	TextureSelector->Render(target);

	// Side bar
	target->draw(SideBar);

	// Cursor text
	target->draw(CursorText);
}

void MapEditorMode::Render(sf::RenderTarget* target)
{
	RenderGui(target);
}


// Private Functions:

void MapEditorMode::InitVariables()
{
	TextureRect = sf::IntRect
	(
		0, 0,
		static_cast<int32>(StData->GridSize),
		static_cast<int32>(StData->GridSize)
	);

	Collision = false;
	Layer = 0;
	AddLocked = false;
}

void MapEditorMode::InitGui()
{
	// Cursor text
	CursorText.setFont(*EditorData->Font);
	CursorText.setFillColor(sf::Color::White);
	CursorText.setCharacterSize(gui::CalculateCharSize(2.f, StData->GfxSettings->Resolution));
	CursorText.setPosition
	(
		static_cast<float>(EditorData->MousePositionWindow->x) + 100.f, 
		static_cast<float>(EditorData->MousePositionWindow->y) - 100.f
	);
	
	// Sidebar
	SideBar.setSize(sf::Vector2f(StData->GridSize, static_cast<float>(StData->GfxSettings->Resolution.height)));
	SideBar.setFillColor(sf::Color(50, 50, 50, 100));
	SideBar.setOutlineColor(sf::Color(200, 200, 200, 150));
	SideBar.setOutlineThickness(-1.f);

	// Tile selector
	SelectorRect.setSize(sf::Vector2f(StData->GridSize, StData->GridSize));
	SelectorRect.setFillColor(sf::Color(255, 255, 255, 150));
	SelectorRect.setOutlineColor(sf::Color::Green);
	SelectorRect.setOutlineThickness(-1.f);
	SelectorRect.setTexture(Map->GetTileSheet());
	SelectorRect.setTextureRect(TextureRect);

	// Texture selector
	TextureSelector = new gui::TextureSelector(10.f, 20.f, StData->GridSize, *Map->GetTileSheet());
}
