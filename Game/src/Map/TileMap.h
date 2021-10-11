#pragma once

#include "Tile.h"

class TileMap
{
public:

// Constructors and Destructor:

	TileMap(float gridSize, int32 gridWidth, int32 gridHeight, int32 layers, std::string textureFilePath);
	TileMap(const std::string& filePath);

	~TileMap();

// Functions:

	// Tekes three indices frpm the mouse position in the grid and adds a tile to that position,
	// if the internal tilemap array allows it.
	void AddTile(const int32 x, const int32 y, const int32 z, const sf::IntRect& textureRect, const bool collision);

	// Tekes three indices frpm the mouse position in the grid and removes a tile on that position,
	// if the internal tilemap array allows it.
	void RemoveTile(const int32 x, const int32 y, const int32 z);

	void Save(const std::string& filePath);

	void Load(const std::string& filePath);

	void UpdateMapBoundsCollision(Player* player, const float& dt);
	void UpdateMapBoundsCollision(Entity* entity, const float& dt);

	void UpdateTileCollision(Player* player, const float& dt);
	void UpdateTileCollision(Entity* entity, const float& dt);	

	void UpdateTiles(Entity* entity, const float& dt);

	void Update(Entity* entity, const float& dt);

	void Render(sf::RenderTarget* target, const sf::Vector2i& gridPosition, const bool showCollision);

// Accessors:

	// Use grid positions.
	const bool SectionEmpty(const int32 x, const int32 y, const int32 z) const;

	const sf::Texture* GetTileSheet() const;

	// Use grid positions.
	const int32 GetLayerSize(const int32 x, const int32 y, const int32 z) const;

	const int32& GetLayer();

	const sf::Vector2i& GetSizeGrid() const;

	const sf::Vector2f& GetSizeF() const;

	// Use grid positions.
	Tile* GetTile(const int32 x, const int32 y, const int32 z);
	// Use grid positions.
	Tile* GetTile(const int32 x, const int32 y);

private:

// Functions:

	void InitTexture(sf::Texture& textue, const std::string& filaPath);

	void ClearMap();

	void ResetMapSize();

// Variables:

	// Logger
	Logger Log;

	// Core
	float GridSizeF;
	int32 GridSizeI;
	sf::Vector2i MapSizeGrid;
	sf::Vector2f MapSizeF;
	int32 LayersMax;
	std::vector<std::vector<std::vector<std::vector<Tile*>>>> Map;
	std::stack<Tile*> DefferedRenderStack;
	std::string TextureFilePath;
	sf::Texture TileSheet;

	// Culling
	int32 FromX;
	int32 ToX;
	int32 FromY;
	int32 ToY;
	int32 Layer;
	int32 CollisionResult;
};

