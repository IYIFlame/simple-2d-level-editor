#pragma once
#include <SFML/Graphics.hpp>
#include "CommonConstants.h"

struct TileConfig{
public:
	TileConfigID id;
	sf::Color colour;
	sf::Vector2f levelEditorSize;
	sf::Vector2f inGameSize;

	TileConfig(TileConfigID newID, sf::Color newColour, sf::Vector2f newlevelEditorSize, sf::Vector2f newInGameSize){
		id = newID; colour = newColour; levelEditorSize = newlevelEditorSize; inGameSize = newInGameSize;
	};
};

struct TileConfigsCollection{
	TileConfig green = TileConfig(GREEN, sf::Color::Color(0, 255, 0, 255), sf::Vector2f(TILE_SIZE, TILE_SIZE), sf::Vector2f(TILE_SIZE, TILE_SIZE));
	TileConfig red = TileConfig(RED, sf::Color::Color(255, 0, 0, 255), sf::Vector2f(TILE_SIZE, TILE_SIZE), sf::Vector2f(TILE_SIZE, TILE_SIZE * 3));
	TileConfig character = TileConfig(CHARACTER, sf::Color::Color(0, 0, 255, 255), sf::Vector2f(TILE_SIZE, TILE_SIZE), sf::Vector2f(TILE_SIZE, TILE_SIZE));

	//remember to add all of the above in here
	const std::vector<TileConfig> configs = {green, red, character};
	TileConfig operator[](int id){
		return configs[id];
	};
};

static TileConfigsCollection TileConfigsCollectionGlobal;

//consider saving the config we are currently using and store information such as the id only there
class Tile{
public:
	TileConfigID id;
	sf::RectangleShape shape;
	sf::Vector2f position;
	int height;

	Tile::Tile(){};
	Tile::Tile(TileConfig config, RunningContextTypes mode = CONTEXT_LEVEL_EDITOR){ applyTileConfig(config, mode); };
	Tile::Tile(sf::Vector2f pos){ position = pos; shape = sf::RectangleShape(pos); };
	void applyTileConfig(TileConfig config, RunningContextTypes mode){
		id = config.id;  shape.setFillColor(config.colour);
		if(mode == CONTEXT_LEVEL_EDITOR){
			height = config.levelEditorSize.y;
			shape.setSize(config.levelEditorSize);
		}
		else if(mode == CONTEXT_GAME){
			height = config.inGameSize.y;
			shape.setSize(config.inGameSize);
		}
	};
};