#pragma once
#include <vector>
#include <fstream>

#include "TileLib.h"
#include "Character.h"
#include "CommonConstants.h"
#include "CommonHelperFunctions.h"

class WorldInterface{
private:
	static WorldInterface* _instance;
	static Tiles levelEditorTiles;
	static Tiles gameTiles;
	static unsigned int loadedMapWidth;
	static unsigned int loadedMapHeight;

	WorldInterface(){};

public:
	static WorldInterface* getInstance();
	static void initMap();
	static void initEmptyMap();
	static int getNumber(char*, int&);
	static void exportMap(const std::string, Character*);//think about passing character pos instead of whole character
	static sf::Vector2f importMap(const std::string);
	static void applyTileConfig(int posX, int posY, TileConfigID tileConfigID);
	void WorldInterface::drawTiles(sf::RenderWindow*, RunningContextTypes);
	//static void rotateWorld();
};
