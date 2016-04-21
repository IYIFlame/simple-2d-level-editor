#pragma once
#include "CommonConstants.h"
#include "RunningContext.h"
#include "Character.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>


class TestGame:public RunningContext{
public:
	TestGame(){};
	TestGame(sf::RenderWindow* newWindow){
		printf("creating window\n");
		testWindow = newWindow;
	};
	virtual ~TestGame(){
		testWindow->close();
		delete testWindow;
	};
	virtual sf::RenderWindow* getWindow(){
		return testWindow;
	};
	RunningContextTypes getContextType(){
		return contextType;
	};
	CurrentViewport getCurrentViewport(){
		return character->getCurrentViewport();
	};
	void setCurrentViewport(CurrentViewport newViewport){
		character->setCurrentViewport(newViewport);
	}
	sf::View* getCamera(){
		return character->getCamera();
	};
	sf::Vector2f getCharacterPos(){
		return character->getPosition();
	};

	virtual Status update(float dt){
		//TODO: we should only draw the things that are visible to the camera not everything so use cameraPos
		if(!error){
			int rows = MAP_SIZE_HEIGHT / TILE_SIZE + 1;
			int columns = MAP_SIZE_WIDTH / TILE_SIZE;
			for(int i = 0; i < rows; ++i){
				for(int j = 0; j < columns; ++j){
					if(tiles[i][j] != NULL){
						testWindow->draw(tiles[i][j]->shape);
					}
				}
			}
		}
		if(character != NULL){
			character->modeGameUpdate();
			testWindow->draw(character->shape);
		}		

		return RUNNING;
	};
	//todo comment these out
	Tiles tiles;//oh god moar hackz(this is used in main)

	Tiles& getTiles(){
		return tiles;
	};

private:
	int MAP_SIZE_WIDTH;
	int MAP_SIZE_HEIGHT;
	sf::RenderWindow* testWindow = NULL;
	Character* character = NULL;
	RunningContextTypes contextType = CONTEXT_GAME;

	bool error = true;// remove this

	//void initEmptyMap(){
	//	int rows = MAP_SIZE_HEIGHT / TILE_SIZE + 1;
	//	int columns = MAP_SIZE_WIDTH / TILE_SIZE;
	//	printf("rows %d columns %d\n", rows, columns);
	//	for(int i = 0; i < rows; ++i){
	//		std::vector<Tile*> row;

	//		for(int j = 0; j < columns; ++j){
	//			Tile* tile = new Tile(sf::Vector2f(j * TILE_SIZE, i * TILE_SIZE));
	//			tile->shape.setFillColor(sf::Color::Magenta);
	//			tile->shape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	//			//tile->shape.setPosition(sf::Vector2f(j * TILE_SIZE, i * TILE_SIZE));
	//			printf("y %d x %d\n", j * TILE_SIZE, i * TILE_SIZE);
	//			row.push_back(tile);
	//		}
	//		tiles.push_back(row);
	//	}
	//	error = false;
	//};

	//int getNumber(char* buffer, int& index){
	//	using namespace std;
	//	string number = "";
	//	while(buffer[index] != ';' && buffer[index] != ':'){
	//		number += buffer[index++];
	//	}
	//	return stoll(number);
	//};
	
	//const std::string pathName = "C:\\Users\\flame\\Source\\Repos\\simple-2d-level-editor\\simple-2d-level-editor\\simple-2d-level-editor\\";
	//void importMap(const std::string fileName){
	//	printf("importing\n");

	//	const std::string fullname = pathName + fileName;
	//	std::ifstream file;
	//	file.open(fullname);

	//	if(file){
	//		int length = 50;//magic value
	//		char * buffer = new char[length]{};
	//		while(!file.eof()){
	//			file.getline(buffer, length);
	//			Tile* tile;
	//			int configID;
	//			int index = 0;

	//			TileConfigID id;
	//			int posX, posY;

	//			while(buffer[index] != 0){

	//				switch(buffer[index]){
	//					case ';':
	//						++index;
	//						break;
	//					case ':':
	//						++index;
	//						break;
	//					case MAP_SIZE:
	//						MAP_SIZE_WIDTH = getNumber(buffer, ++index);
	//						MAP_SIZE_HEIGHT = getNumber(buffer, ++index);
	//						initEmptyMap();
	//						break;
	//					case ID:
	//						configID = getNumber(buffer, ++index);
	//						break;
	//					case POSITION:
	//						posX = getNumber(buffer, ++index);
	//						posY = getNumber(buffer, ++index);
	//						if(configID == CHARACTER){
	//							character = new Character(posX, posY, CONTEXT_GAME);
	//							character->setCurrentWindow(testWindow);
	//						}
	//						else{
	//							tile = tiles[posY / TILE_SIZE][posX / TILE_SIZE];
	//						
	//							tile->applyTileConfig(TileConfigsCollectionGlobal[configID], CONTEXT_GAME);
	//							tile->shape.setPosition(posX, GAME_RES_HEIGHT - tile->height);
	//						}
	//						break;
	//					default :
	//						printf("ERROR unrecognized symbol %c in line %s", buffer[index], buffer);
	//						file.close();
	//						delete[] buffer;
	//						break;
	//				}
	//			}
	//		}
	//		file.close();
	//		delete[] buffer;
	//	}
	//};
};