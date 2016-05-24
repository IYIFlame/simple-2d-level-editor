#include "WorldInterface.h"

WorldInterface::WorldInterface(){
	tiles = new Tiles();
}

WorldInterface::WorldInterface(RunningContextTypes contextType){
	this->contextType = contextType;
	tiles = new Tiles();
}

WorldInterface::~WorldInterface(){
	TileVector row;
	//TODO: remake it to use loaded_map_width and height
	for(int i = 0; i < tiles->size(); ++i){
		row = tiles->at(i);
		for(int j = 0; j < row.size(); ++j){
			delete row[j];
		}
	}
	delete tiles;
}

void WorldInterface::setContextType(RunningContextTypes contextType){
	this->contextType = contextType;
}

Tiles* WorldInterface::getRunningContextTiles(){
	return tiles;
}

void WorldInterface::getLoadedMapHeightAndWidth(int& height, int& width){
	height = loadedMapHeight;
	width = loadedMapWidth;
}

void WorldInterface::initMap(){
	printf("Initializing empty map\n");

	TileConfig tileConfig = TileConfigsCollectionGlobal[INVALID];
	if(contextType == CONTEXT_LEVEL_EDITOR){
		tileConfig = TileConfigsCollectionGlobal[GREEN];
	}

	int rows = MAP_SIZE_HEIGHT;
	int columns = MAP_SIZE_WIDTH;
	getRowsAndCols(rows, columns);

	printf("rows %d columns %d\n", rows, columns);
	for(int i = 0; i < rows; ++i){
		std::vector<Tile*> row;

		for(int j = 0; j < columns; ++j){
			Tile* tile = new Tile();
			tile->applyTileConfig(tileConfig, contextType);
			tile->shape.setPosition(sf::Vector2f(j * TILE_SIZE, i * TILE_SIZE));
			//printf("y %d x %d\n", j * TILE_SIZE, i * TILE_SIZE);
			row.push_back(tile);
		}
		tiles->push_back(row);
	}
}

const std::string pathName = "C:\\Users\\flame\\Source\\Repos\\simple-2d-level-editor\\simple-2d-level-editor\\simple-2d-level-editor\\";
void WorldInterface::exportMap(const std::string fileName, Character* character){
	static const char tagMapSize = char(MAP_SIZE);
	static const char tagID = char(ID);
	static const char tagPosition = char(POSITION);

	printf("Exporting map...");
	std::ofstream file;
	file.open(pathName + fileName);

	int rows = MAP_SIZE_HEIGHT;
	int columns = MAP_SIZE_WIDTH;
	getRowsAndCols(rows, columns);

	file << tagMapSize << MAP_SIZE_WIDTH << ";" << MAP_SIZE_HEIGHT << ";\n";
	if(character != NULL){
		file << tagID << character->id << ";" << tagPosition << character->startPosition.x;
		file << ":" << character->startPosition.y << ";\n";
	}

	for(int i = 0; i < rows; ++i){
		for(int j = 0; j < columns; ++j){
			if((*tiles)[i][j] != NULL){
				auto tileShape = (*tiles)[i][j]->shape;
				TileConfigID id = (*tiles)[i][j]->id;
				int posX = tileShape.getPosition().x;
				int posY = tileShape.getPosition().y;

				file << tagID << id << ";" << tagPosition << posX << ":" << posY << ";\n";
			}
		}
	}
	printf("Complete!\n");
	file.close();
}

int WorldInterface::getNumber(char* buffer, int& index){
	using namespace std;
	string number = "";
	while(buffer[index] != ';' && buffer[index] != ':'){
		number += buffer[index++];
	}
	return stoll(number);
}

sf::Vector2f WorldInterface::importMap(const std::string fileName){
	printf("importing\n");

	sf::Vector2f characterPosition = sf::Vector2f(0.f, 0.f);
	const std::string fullname = pathName + fileName;
	std::ifstream file;
	file.open(fullname);

	if(file){
		int length = 50;//magic value
		char * buffer = new char[length]{};
		while(!file.eof()){
			file.getline(buffer, length);

			Tile* tile;
			int configID;
			int index = 0;

			TileConfigID id;
			int posX, posY;

			while(buffer[index] != 0){

				switch(buffer[index]){
					case ';':
						++index;
						break;
					case ':':
						++index;
						break;
					case MAP_SIZE:
						loadedMapWidth = getNumber(buffer, ++index);
						loadedMapHeight = getNumber(buffer, ++index);
						initMap();
						break;
					case ID:
						configID = getNumber(buffer, ++index);
						break;
					case POSITION:
						posX = getNumber(buffer, ++index);
						posY = getNumber(buffer, ++index);
						if(configID == CHARACTER){
							//character = new Character(posX, posY, CONTEXT_GAME);
							//character->setCurrentWindow(testWindow);
							characterPosition = sf::Vector2f(posX, posY);
						}
						else{
							tile = (*tiles)[posY / TILE_SIZE][posX / TILE_SIZE];

							tile->applyTileConfig(TileConfigsCollectionGlobal[configID], CONTEXT_GAME);
							tile->shape.setPosition(posX, GAME_RES_HEIGHT - tile->height);
						}
						break;
					default:
						printf("ERROR unrecognized symbol %c in line %s", buffer[index], buffer);
						file.close();
						delete[] buffer;
						return characterPosition;
				}
			}
		}
		file.close();
		delete[] buffer;

		return characterPosition;
	}
}

void WorldInterface::applyTileConfig(int posX, int posY, TileConfigID tileConfigID){
	Tile* tile = (*tiles)[posY / TILE_SIZE][posX / TILE_SIZE];
	tile->applyTileConfig(TileConfigsCollectionGlobal[tileConfigID], CONTEXT_LEVEL_EDITOR);//TODO hardcoded enum
}
