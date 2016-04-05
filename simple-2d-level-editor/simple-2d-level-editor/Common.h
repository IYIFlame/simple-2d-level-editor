#pragma once
#include <SFML/Graphics.hpp>
#include <map>

//for update functions
enum Status{
	NOT_RUNNING,
	RUNNING,
	EXITING,
};

// for exporting the map(find a way to use for import)
enum MapEntryTypeID{
	MAP_SIZE,
	ID,
	POSITION,
};

//for giving ids to every type of tile we have
enum TileConfigID{
	GREEN,
	RED,
};

const unsigned int TILE_SIZE = 16;

struct TileConfig{
public:
	sf::Color colour;
	sf::Vector2f size;
};

struct TileConfig_Green :public TileConfig{
public:
	TileConfigID id = GREEN;
	sf::Color colour = sf::Color::Green;
	sf::Vector2f size = sf::Vector2f(TILE_SIZE, TILE_SIZE);
};

struct TileConfig_Red :public TileConfig{
public:
	TileConfigID id = RED;
	sf::Color colour = sf::Color::Red;
	sf::Vector2f size = sf::Vector2f(TILE_SIZE, TILE_SIZE*3);
};


//std::map<TileConfigID, TileConfig> enumToTileConfigMapping;
//enumToTileConfigMapping.insert(std::pair<TileConfigID, TileConfig>(GREEN, TileConfig_Green()));

class Tile{
public:
	TileConfigID id;
	sf::RectangleShape shape;

	Tile::Tile(){};
	Tile::Tile(sf::Vector2f position){ shape = sf::RectangleShape(position); };
	void applyTileConfig(TileConfig_Green config){ id = config.id;  shape.setFillColor(config.colour); shape.setSize(config.size); };
	void applyTileConfig(TileConfig_Red config){ id = config.id; shape.setFillColor(config.colour); shape.setSize(config.size); };
};