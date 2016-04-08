#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <deque>

//for update functions
enum Status{
	NOT_RUNNING,
	RUNNING,
	SUSPENDED,
	EXITING,
};

enum RunningMode{
	MODE_LEVEL_EDITOR,
	MODE_GAME,
};

const unsigned int NUMBER_OF_VIEWPORTS = 4;
enum CurrentViewport{
	FIRST,
	SECOND,
	THIRD,
	FOURTH,
	DEFAULT,
};
typedef std::vector<CurrentViewport> ViewportList;
static const ViewportList VIEWPORTS = {FIRST,SECOND,THIRD,FOURTH,DEFAULT,};

enum EventTypes{
	CHANGE_VIEWPORT,
};

typedef std::deque<EventTypes> Events;
class EventQueue{
private:
	static EventQueue* _instance;
	static Events* events;
	EventQueue(){};

public:
	static EventQueue* getInstance();

	static Events* getEvents();
};

// for exporting the map
enum MapEntryTypeID:unsigned char{
	MAP_SIZE = '0',
	ID,
	POSITION,
};

//for giving ids to every type of tile we have
enum TileConfigID{
	GREEN,
	RED,
	CHARACTER,
};

//we moved this here for creating the window it should be renamed, the actual map sizes will vary per map...
const unsigned int MAP_SIZE_WIDTH = 1024;
const unsigned int MAP_SIZE_HEIGHT = 768;
const int GAME_RES_WIDTH = 1024;//??
const int GAME_RES_HEIGHT = 768;
const unsigned int TILE_SIZE = 16;

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
	TileConfig green = TileConfig(GREEN, sf::Color::Color(0,255,0,255), sf::Vector2f(TILE_SIZE, TILE_SIZE), sf::Vector2f(TILE_SIZE, TILE_SIZE));
	TileConfig red = TileConfig(RED, sf::Color::Color(255, 0, 0, 255), sf::Vector2f(TILE_SIZE, TILE_SIZE), sf::Vector2f(TILE_SIZE, TILE_SIZE * 3));
	TileConfig character = TileConfig(CHARACTER, sf::Color::Color(0,0,255,255), sf::Vector2f(TILE_SIZE, TILE_SIZE), sf::Vector2f(TILE_SIZE, TILE_SIZE));
	
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
	Tile::Tile(TileConfig config, RunningMode mode = MODE_LEVEL_EDITOR){ applyTileConfig(config, mode); };
	Tile::Tile(sf::Vector2f pos){ position = pos; shape = sf::RectangleShape(pos); };
	void applyTileConfig(TileConfig config, RunningMode mode){ 
		id = config.id;  shape.setFillColor(config.colour); 
		if(mode == MODE_LEVEL_EDITOR){
			height = config.levelEditorSize.y;
			shape.setSize(config.levelEditorSize); 
		}
		else if(mode == MODE_GAME){
			height = config.inGameSize.y;
			shape.setSize(config.inGameSize);
		}
	};
};