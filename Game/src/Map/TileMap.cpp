#include "../stdafx.h"
#include "TileMap.h"

// Constructors and Destructor:

TileMap::TileMap(float gridSize, int32 gridWidth, int32 gridHeight, int32 layers, std::string textureFilePath)
	: Log(typeid(*this).name())
{
	// Core
	GridSizeF = gridSize;
	GridSizeI = static_cast<int32>(GridSizeF);

	MapSizeGrid.x = gridWidth;
	MapSizeGrid.y = gridHeight;

	MapSizeF.x = static_cast<float>(gridWidth) * gridSize;
	MapSizeF.y = static_cast<float>(gridHeight) * gridSize;

	LayersMax = layers;

	TextureFilePath = textureFilePath;

	// Culling
	FromX = 0;
	ToX = 0;

	FromY = 0;
	ToY = 0;

	CollisionResult = 0;

	Layer = 0;

	// Map resizing
	ResetMapSize();

	// Tile sheet
	InitTexture(TileSheet, textureFilePath);
}

TileMap::TileMap(const std::string& filePath)
	: Log(typeid(*this).name())
{
	// Culling
	FromX = 0;
	ToX = 0;

	FromY = 0;
	ToY = 0;

	Layer = 0;

	// Loading map
	Load(filePath);
}

TileMap::~TileMap()
{
	ClearMap();
}


// Functions:

void TileMap::AddTile(const int32 x, const int32 y, const int32 z, const sf::IntRect& textureRect, const bool collision)
{
	if (x < MapSizeGrid.x && x >= 0 &&
		y < MapSizeGrid.y && y >= 0 &&
		z < LayersMax && z >= 0)
	{
		Map[x][y][z].push_back(new Tile(x, y, GridSizeF, TileSheet, textureRect, collision));

		Log.Trace("AddTile::Tile added");
	}
}

void TileMap::RemoveTile(const int32 x, const int32 y, const int32 z)
{
	if (x < MapSizeGrid.x && x >= 0
		&& y < MapSizeGrid.y && y >= 0
		&& z < LayersMax && z >= 0)
	{
		if (!Map[x][y][z].empty())
		{
			delete Map[x][y][z].back();
			Map[x][y][z].pop_back();

			Log.Trace("RemoveTile::Tile removed");
		}
	}
}

void TileMap::Save(const std::string& filePath)
{
	std::ofstream out;

	out.open(filePath);

	if (out.is_open())
	{
		// Map
		out << MapSizeGrid.x << " " << MapSizeGrid.y << " " << LayersMax << std::endl;
		out << GridSizeI << std::endl;
		out << TextureFilePath << std::endl;

		// Tiles
		for (int32 x = 0; x < MapSizeGrid.x; x++)
		{
			for (int32 y = 0; y < MapSizeGrid.y; y++)
			{
				for (int32 z = 0; z < LayersMax; z++)
				{
					if (!Map[x][y][z].empty())
					{
						for (size_t k = 0; k < Map[x][y][z].size(); k++)
						{
							out << x << " " << y << " " << z << " " << Map[x][y][z][k]->GetAsString() << " ";
						}
					}
				}
			}
		}
	}
	else
	{
		Log.Error("Save::Failed to save to: " + filePath);
	}

	out.close();

	Log.Trace("Save::Map saved");
}

void TileMap::Load(const std::string& filePath)
{
	std::ifstream in;

	in.open(filePath);

	if (in.is_open())
	{
		sf::Vector2i size;
		int32 layersMax = 0;
		int32 gridSize = 0;
		std::string textureFilePath = "";
		int32 x = 0;
		int32 y = 0;
		int32 z = 0;
		int32 textureRectX = 0;
		int32 textureRectY = 0;
		bool collision = false;

		// Map
		in >> size.x >> size.y >> layersMax >> gridSize >> textureFilePath;

		// Clearing map
		ClearMap();

		// Tiles
		GridSizeF = static_cast<float>(gridSize);
		GridSizeI = gridSize;

		MapSizeGrid = size;
		MapSizeF = sf::Vector2f(size * gridSize);
		LayersMax = layersMax;

		TextureFilePath = textureFilePath;

		// Map resizing
		ResetMapSize();

		// Loading tile sheet
		InitTexture(TileSheet, textureFilePath);

		// Loading tiles
		while (in >> x >> y >> z >> textureRectX >> textureRectY >> collision)
		{
			Map[x][y][z].push_back(new Tile(x, y, GridSizeF, TileSheet, sf::IntRect(textureRectX, textureRectY, GridSizeI, GridSizeI), collision));
		}
	}
	else
	{
		Log.Error("Load::Failed to open: " + filePath);
	}

	in.close();

	Log.Trace("Load::Map loaded: " + filePath);
}

void TileMap::UpdateMapBoundsCollision(Player* player, const float& dt)
{
	// World bounds X
	if (player->GetPosition().x - (player->GetGlobalBounds().width / 2.f) < 0.f)
	{
		player->SetPosition(0.f + (player->GetGlobalBounds().width / 2.f), player->GetPosition().y);
		player->InvertVelocityX();
	}
	else if (player->GetPosition().x + (player->GetGlobalBounds().width / 2.f) > MapSizeF.x)
	{
		player->SetPosition(MapSizeF.x - (player->GetGlobalBounds().width / 2.f), player->GetPosition().y);
		player->InvertVelocityX();
	}

	// World bounds X
	if (player->GetPosition().y - (player->GetGlobalBounds().height / 2.f) < 0.f)
	{
		player->SetPosition(player->GetPosition().x, 0.f + (player->GetGlobalBounds().height / 2.f));
		player->InvertVelocityY();
	}
	else if (player->GetPosition().y + (player->GetGlobalBounds().height / 2.f) > MapSizeF.y)
	{
		player->SetPosition(player->GetPosition().x, MapSizeF.y - (player->GetGlobalBounds().height / 2.f));
		player->InvertVelocityY();
	}
}

void TileMap::UpdateMapBoundsCollision(Entity* entity, const float& dt)
{
	// World bounds X
	if (entity->GetPosition().x < 0.f)
	{
		entity->SetPosition(0.f, entity->GetPosition().y);
	}
	else if (entity->GetPosition().x + entity->GetGlobalBounds().width > MapSizeF.x)
	{
		entity->SetPosition(MapSizeF.x - entity->GetGlobalBounds().width, entity->GetPosition().y);
	}

	// World bounds X
	if (entity->GetPosition().y < 0.f)
	{
		entity->SetPosition(entity->GetPosition().x, 0.f);
	}
	else if (entity->GetPosition().y + entity->GetGlobalBounds().height > MapSizeF.y)
	{
		entity->SetPosition(entity->GetPosition().x, MapSizeF.y - entity->GetGlobalBounds().height);
	}
}

void TileMap::UpdateTileCollision(Player* player, const float& dt)
{
	Layer = 0;

	// From X
	FromX = player->GetPositionGrid(GridSizeI).x - 1;

	if (FromX < 0)
	{
		FromX = 0;
	}
	else if (FromX > MapSizeGrid.x)
	{
		FromX = MapSizeGrid.x;
	}

	// To X
	ToX = player->GetPositionGrid(GridSizeI).x + 3;

	if (ToX < 0)
	{
		ToX = 0;
	}
	else if (ToX > MapSizeGrid.x)
	{
		ToX = MapSizeGrid.x;
	}

	// From Y
	FromY = player->GetPositionGrid(GridSizeI).y - 1;

	if (FromY < 0)
	{
		FromY = 0;
	}
	else if (FromY > MapSizeGrid.y)
	{
		FromY = MapSizeGrid.y;
	}

	// To Y
	ToY = player->GetPositionGrid(GridSizeI).y + 3;

	if (ToY < 0)
	{
		ToY = 0;
	}
	else if (ToY > MapSizeGrid.y)
	{
		ToY = MapSizeGrid.y;
	}
	
	for (int32 x = FromX; x < ToX; x++)
	{
		for (int32 y = FromY; y < ToY; y++)
		{
			for (size_t k = 0; k < Map[x][y][Layer].size(); k++)
			{
				if (!Map[x][y][Layer].empty())
				{
					if (Map[x][y][Layer][k]->GetCollision())
					{
						CollisionResult = Map[x][y][Layer][k]->GetCollider().CheckCollision(player->GetCollider(), 1.f);

						switch (CollisionResult)
						{
							case 1:
							{
								player->InvertVelocityX();

								break;
							}

							case 2:
							{
								player->InvertVelocityY();

								break;
							}
						}
					}					
				}
			}
		}
	}
}

void TileMap::UpdateTileCollision(Entity* entity, const float& dt)
{
	// To do...
}

void TileMap::UpdateTiles(Entity* entity, const float& dt)
{
	// To do...
}

void TileMap::Update(Entity* entity, const float& dt)
{
	// To do...
}

void TileMap::Render(sf::RenderTarget* target, const sf::Vector2i& gridPosition, const bool showCollision)
{
	Layer = 0;

	// From X
	FromX = gridPosition.x - 15;

	if (FromX < 0)
	{
		FromX = 0;
	}
	else if (FromX > MapSizeGrid.x)
	{
		FromX = MapSizeGrid.x;
	}

	// To X
	ToX = gridPosition.x + 16;

	if (ToX < 0)
	{
		ToX = 0;
	}
	else if (ToX > MapSizeGrid.x)
	{
		ToX = MapSizeGrid.x;
	}

	// From Y
	FromY = gridPosition.y - 15;

	if (FromY < 0)
	{
		FromY = 0;
	}
	else if (FromY > MapSizeGrid.y)
	{
		FromY = MapSizeGrid.y;
	}

	// To Y
	ToY = gridPosition.y + 16;

	if (ToY < 0)
	{
		ToY = 0;
	}
	else if (ToY > MapSizeGrid.y)
	{
		ToY = MapSizeGrid.y;
	}

	// Rendeing
	for (int32 x = FromX; x < ToX; x++)
	{
		for (int32 y = FromY; y < ToY; y++)
		{
			for (size_t k = 0; k < Map[x][y][Layer].size(); k++)
			{
				if (!Map[x][y][Layer].empty())
				{
					Map[x][y][Layer][k]->Render(target, showCollision);
				}
			}
		}
	}
}


// Accessors:

const bool TileMap::SectionEmpty(const int32 x, const int32 y, const int32 z) const
{
	if (x >= 0 && x < MapSizeGrid.x &&
		y >= 0 && y < MapSizeGrid.y &&
		z >= 0 && z < LayersMax)
	{
		return Map[x][y][z].empty();
	}

	return false;
}

const sf::Texture* TileMap::GetTileSheet() const
{
	return &TileSheet;
}

const int32 TileMap::GetLayerSize(const int32 x, const int32 y, const int32 z) const
{
	if (x >= 0 && x < static_cast<int32>(Map.size()))
	{
		if (y >= 0 && y < static_cast<int32>(Map[x].size()))
		{
			if (z >= 0 && z < static_cast<int32>(Map[x][y].size()))
			{
				return static_cast<int32>(Map[x][y][z].size());
			}
		}
	}

	// If no tiles
	return 0;
}

const int32& TileMap::GetLayer()
{
	return Layer;
}

const sf::Vector2i& TileMap::GetSizeGrid() const
{
	return MapSizeGrid;
}

const sf::Vector2f& TileMap::GetSizeF() const
{
	return MapSizeF;
}

Tile* TileMap::GetTile(const int32 x, const int32 y, const int32 z)
{
	if (x >= 0 && x < MapSizeGrid.x &&
		y >= 0 && y < MapSizeGrid.y &&
		z >= 0 && z < LayersMax)
	{
		if (!Map[x][y][z].empty())
		{
			return Map[x][y][z].back();
		}
	}

	return nullptr;
}

Tile* TileMap::GetTile(const int32 x, const int32 y)
{
	if (x >= 0 && x < MapSizeGrid.x &&
		y >= 0 && y < MapSizeGrid.y)
	{
		if (!Map[x][y].back().empty())
		{
			return Map[x][y].back().back();
		}
	}

	return nullptr;
}


// Private Functions:

void TileMap::InitTexture(sf::Texture& texture, const std::string& filaPath)
{
	if (!texture.loadFromFile(filaPath))
	{
		Log.Error("InitTexture::Failed to load: " + filaPath);
	}
	else
	{
		Log.Trace("Tile map initialized");
	}
}

void TileMap::ClearMap()
{
	for (size_t x = 0; x < Map.size(); x++)
	{
		for (size_t y = 0; y < Map[x].size(); y++)
		{
			for (size_t z = 0; z < Map[x][y].size(); z++)
			{
				for (size_t k = 0; k < Map[x][y][z].size(); k++)
				{
					delete Map[x][y][z][k];
					Map[x][y][z][k] = nullptr;
				}
				Map[x][y][z].clear();
			}
			Map[x][y].clear();
		}
		Map[x].clear();
	}
	Map.clear();

	Log.Trace("ClearMap::Map cleared");
}

void TileMap::ResetMapSize()
{
	Map.resize(MapSizeGrid.x, std::vector<std::vector<std::vector<Tile*>>>());

	for (int32 x = 0; x < MapSizeGrid.x; x++)
	{
		for (int32 y = 0; y < MapSizeGrid.y; y++)
		{
			Map[x].resize(MapSizeGrid.y, std::vector<std::vector<Tile*>>());

			for (int32 z = 0; z < LayersMax; z++)
			{
				Map[x][y].resize(LayersMax, std::vector<Tile*>());
			}
		}
	}

	Log.Trace("ResetMapSize::Map size reset");
}
