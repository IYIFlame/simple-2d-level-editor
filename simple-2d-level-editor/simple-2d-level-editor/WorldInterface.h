#pragma once
#include <vector>
#include <fstream>

#include "TileLib.h"
#include "Character.h"
#include "CommonConstants.h"
#include "CommonHelperFunctions.h"

class WorldInterface{
	RunningContextTypes contextType = CONTEXT_INVALID;
	Tiles* tiles = NULL;
	unsigned int loadedMapWidth;//TODO: when looping we should always be using this instead of size or MAP_WIDTH and HEIGHT
	unsigned int loadedMapHeight;

	int getNumber(char*, int&);//TODO prolly should be private
public:

	WorldInterface();
	
	WorldInterface(RunningContextTypes);

	~WorldInterface();

	void setContextType(RunningContextTypes);

	Tiles* getRunningContextTiles();

	void getLoadedMapHeightAndWidth(int&, int&);

	void initMap();

	//void initEmptyMap();

	void exportMap(const std::string, Character*);//think about passing character pos instead of whole character

	sf::Vector2f importMap(const std::string);

	void applyTileConfig(int posX, int posY, TileConfigID tileConfigID);

	//static void rotateWorld(); //TODO should this be here?
};
