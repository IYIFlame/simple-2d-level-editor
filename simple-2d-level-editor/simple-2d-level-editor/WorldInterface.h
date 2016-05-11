#pragma once
#include <vector>
#include <fstream>

#include "TileLib.h"
#include "Character.h"
#include "WindowManager.h"
#include "CommonConstants.h"
#include "CommonHelperFunctions.h"

class WorldInterface{
private:
	static WorldInterface* _instance;
	static Tiles* levelEditorTiles;
	static Tiles* gameTiles;
	static unsigned int loadedMapWidth;
	static unsigned int loadedMapHeight;

	WorldInterface(){};
public:
	static WorldInterface* getInstance();
	static Tiles* getRunningContextTiles(RunningContextTypes);
	static void getLoadedMapHeightAndWidth(int&, int&);

	static void initMap();
	static void initEmptyMap();
	static int getNumber(char*, int&);//prolly should be private
	static void exportMap(const std::string, Character*);//think about passing character pos instead of whole character
	static sf::Vector2f importMap(const std::string);
	static void applyTileConfig(int posX, int posY, TileConfigID tileConfigID);
	static void WorldInterface::drawTiles(sf::RenderWindow*, RunningContextTypes);
	//static void rotateWorld();
};
