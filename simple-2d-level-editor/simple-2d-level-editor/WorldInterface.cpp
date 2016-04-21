#include "WorldInterface.h"

WorldInterface* WorldInterface::_instance = NULL;

WorldInterface* WorldInterface::getInstance(){
	if(_instance == NULL)
		_instance = new WorldInterface(); //Not thread-safe version
	return _instance;

	//Note that _instance is *never* deleted - 
	//it exists for the entire lifetime of the program!
}

void WorldInterface::initMap(){
	int rows = MAP_SIZE_HEIGHT;
	int columns = MAP_SIZE_WIDTH;
	getRowsAndCols(rows, columns);

	printf("rows %d columns %d\n", rows, columns);
	for(int i = 0; i < rows; ++i){
		std::vector<Tile*> row;

		for(int j = 0; j < columns; ++j){
			Tile* tile = new Tile();
			tile->applyTileConfig(TileConfigsCollectionGlobal[GREEN], CONTEXT_LEVEL_EDITOR);
			tile->shape.setPosition(sf::Vector2f(j * TILE_SIZE, i * TILE_SIZE));
			printf("y %d x %d\n", j * TILE_SIZE, i * TILE_SIZE);
			row.push_back(tile);
		}
		levelEditorTiles.push_back(row);
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
			if(levelEditorTiles[i][j] != NULL){
				auto tileShape = levelEditorTiles[i][j]->shape;
				TileConfigID id = levelEditorTiles[i][j]->id;
				int posX = tileShape.getPosition().x;
				int posY = tileShape.getPosition().y;

				file << tagID << id << ";" << tagPosition << posX << ":" << posY << ";\n";
			}
		}
	}
	printf("Complete!\n");
	file.close();
}

//merge this and initMap into one function, give RunningContextTypes, mapWidth and height as parameters
void WorldInterface::initEmptyMap(){
	int rows = MAP_SIZE_HEIGHT / TILE_SIZE + 1;
	int columns = MAP_SIZE_WIDTH / TILE_SIZE;
	printf("rows %d columns %d\n", rows, columns);
	for(int i = 0; i < rows; ++i){
		std::vector<Tile*> row;

		for(int j = 0; j < columns; ++j){
			Tile* tile = new Tile(sf::Vector2f(j * TILE_SIZE, i * TILE_SIZE));
			tile->shape.setFillColor(sf::Color::Magenta);
			tile->shape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
			printf("y %d x %d\n", j * TILE_SIZE, i * TILE_SIZE);
			row.push_back(tile);
		}
		gameTiles.push_back(row);
	}
	//error = false;
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
						initEmptyMap();
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
							tile = gameTiles[posY / TILE_SIZE][posX / TILE_SIZE];

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
	Tile* tile = levelEditorTiles[posY / TILE_SIZE][posX / TILE_SIZE];
	tile->applyTileConfig(TileConfigsCollectionGlobal[tileConfigID], CONTEXT_LEVEL_EDITOR);
}

void WorldInterface::drawTiles(sf::RenderWindow* currentWindow, RunningContextTypes contextType){
	int rows = MAP_SIZE_HEIGHT;
	int columns = MAP_SIZE_WIDTH;
	getRowsAndCols(rows, columns);
	Tiles tiles;

	if(contextType == CONTEXT_LEVEL_EDITOR){
		tiles = levelEditorTiles;
	}
	else if(contextType == CONTEXT_GAME){
		tiles = gameTiles;
	}
	else{
		//PRINT_ERROR
	}

	for(int i = 0; i < rows; ++i){
		for(int j = 0; j < columns; ++j){
			if(tiles[i][j] != NULL){
				currentWindow->draw(tiles[i][j]->shape);
			}
		}
	}
}
