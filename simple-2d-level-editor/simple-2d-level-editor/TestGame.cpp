#pragma once
#include "Common.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>


class TestGame{
public:
	TestGame(){
		printf("creating window\n");
		testWindow = new sf::RenderWindow(sf::VideoMode(GAME_RES_WIDTH, GAME_RES_HEIGHT), "FOCKEN OP GAEM M8");
	};
	~TestGame(){
		delete testWindow;
	};

	Status update(float dt){
		sf::Event event;
		if(testWindow->pollEvent(event)){ 
			if(event.type == sf::Event::Closed){
				testWindow->close();
				return EXITING;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				testWindow->close();
				return EXITING;
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
				std::string fileName = "test.txt";
				importMap(fileName);
			}
		}
		testWindow->clear();
		if(!error){
			int rows = cameraPos.y / TILE_SIZE + 1;
			int columns = cameraPos.x / TILE_SIZE + 3;
			for(int i = 0; i <= rows; ++i){
				for(int j = cameraPos.x / TILE_SIZE - 3; j < columns; ++j){
					if(tiles[i][j] != NULL){
						testWindow->draw(tiles[i][j]->shape);
					}
				}
			}
		}

		testWindow->display();
		return RUNNING;
	};

private:
	const int GAME_RES_WIDTH = 800;//??
	const int GAME_RES_HEIGHT = 600;
	int MAP_SIZE_WIDTH;
	int MAP_SIZE_HEIGHT;
	sf::RenderWindow* testWindow = NULL;

	sf::Vector2f cameraPos = sf::Vector2f(80, 80);
	bool error = true;//remove this 
	
	typedef std::vector< std::vector<Tile*> > Tiles;
	Tiles tiles;

	void initEmptyMap(){
		int rows = MAP_SIZE_HEIGHT / TILE_SIZE + 1;
		int columns = MAP_SIZE_WIDTH / TILE_SIZE;
		printf("rows %d columns %d\n", rows, columns);
		for(int i = 0; i < rows; ++i){
			std::vector<Tile*> row;

			for(int j = 0; j < columns; ++j){
				Tile* tile = new Tile();
				tile->shape.setFillColor(sf::Color::Magenta);
				tile->shape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
				tile->shape.setPosition(sf::Vector2f(j * TILE_SIZE, i * TILE_SIZE));
				printf("y %d x %d\n", j * TILE_SIZE, i * TILE_SIZE);
				row.push_back(tile);
			}
			tiles.push_back(row);
		}
		error = false;
	};

	int getNumber(char* buffer, int& index){
		using namespace std;
		string number = "";
		while(buffer[index] != ';' && buffer[index] != ':'){
			number += buffer[index++];
		}
		return stoll(number);
	};
	
	const std::string pathName = "C:\\Users\\flame\\Source\\Repos\\simple-2d-level-editor\\simple-2d-level-editor\\simple-2d-level-editor\\";
	int importMap(const std::string fileName){
		printf("importing\n");

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
							MAP_SIZE_WIDTH = getNumber(buffer, ++index);
							MAP_SIZE_HEIGHT = getNumber(buffer, ++index);
							initEmptyMap();
							break;
						case ID:
							configID = getNumber(buffer, ++index);
							break;
						case POSITION:
							posX = getNumber(buffer, ++index);
							posY = getNumber(buffer, ++index);
							tile = tiles[posY / TILE_SIZE][posX / TILE_SIZE];
							
							tile->applyTileConfig(TileConfigsCollectionGlobal[configID], MODE_GAME);
							tile->shape.setPosition(posX, GAME_RES_HEIGHT - tile->height);

							break;
						default :
							printf("ERROR unrecognized symbol %c in line %s", buffer[index], buffer);
							file.close();
							delete[] buffer;					
							return 0;
							break;
					}
				}
			}
			file.close();
			delete[] buffer;
		}
		return 1;
	};
};