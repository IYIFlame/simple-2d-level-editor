#pragma once
#include "Common.h"
#include "Character.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

class LevelEditor{
public:
	LevelEditor(){};
	LevelEditor(sf::RenderWindow* newWindow){
		window = newWindow;
		initMap();
	}
	~LevelEditor(){
		delete window;
	};

	sf::RenderWindow* getWindow(){
		return window;
	};
	
	inline bool outOfWindowBounds(int x, int y){
		return x > MAP_SIZE_WIDTH || y > MAP_SIZE_HEIGHT;
	}

	Status update(){
		sf::Event event;
		if(window->pollEvent(event)){
			if(event.type == sf::Event::Closed){
				return EXITING;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				return EXITING;
			}

			sf::Vector2i position = sf::Mouse::getPosition(*window);
			int posX = position.x;
			int posY = position.y;

			if(outOfWindowBounds(posX, posY)){
				return RUNNING;
			}

			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				printf("%d %d %d %d\n", position.x, position.y, position.x / TILE_SIZE, position.y / TILE_SIZE);
				tiles[posY / TILE_SIZE][posX / TILE_SIZE]->applyTileConfig(TileConfigsCollectionGlobal[GREEN], MODE_LEVEL_EDITOR);
			}

			if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
				printf("%d %d %d %d\n", position.x, position.y, position.x / TILE_SIZE, position.y / TILE_SIZE);
				tiles[posY / TILE_SIZE][posX / TILE_SIZE]->applyTileConfig(TileConfigsCollectionGlobal[RED], MODE_LEVEL_EDITOR);
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
				std::string fileName = "test.txt";
				exportMap(fileName);
			}

		}

		int rows = MAP_SIZE_HEIGHT / TILE_SIZE + 1;
		int columns = MAP_SIZE_WIDTH / TILE_SIZE;
		for(int i = 0; i < rows; ++i){
			for(int j = 0; j < columns; ++j){
				if(tiles[i][j] != NULL){
					window->draw(tiles[i][j]->shape);
				}
			}
		}
		
		return RUNNING;
	};

private:
	sf::RenderWindow* window = NULL;

	typedef std::vector< std::vector<Tile*> > Tiles;
	Tiles tiles;

	void initMap(){
		int rows = MAP_SIZE_HEIGHT / TILE_SIZE + 1;
		int columns = MAP_SIZE_WIDTH / TILE_SIZE;
		printf("rows %d columns %d\n", rows, columns);
		for(int i = 0; i < rows; ++i){
			std::vector<Tile*> row;

			for(int j = 0; j < columns; ++j){
				Tile* tile = new Tile();
				tile->applyTileConfig(TileConfigsCollectionGlobal[GREEN], MODE_LEVEL_EDITOR);
				tile->shape.setPosition(sf::Vector2f(j * TILE_SIZE, i * TILE_SIZE));
				printf("y %d x %d\n", j * TILE_SIZE, i * TILE_SIZE);
				row.push_back(tile);
			}
			tiles.push_back(row);
		}
	};

	const std::string pathName = "C:\\Users\\flame\\Source\\Repos\\simple-2d-level-editor\\simple-2d-level-editor\\simple-2d-level-editor\\";
	int exportMap(const std::string fileName){
		static const char tagMapSize = char(MAP_SIZE);
		static const char tagID = char(ID);
		static const char tagPosition = char(POSITION);

		printf("Exporting map...");
		std::ofstream file;
		file.open(pathName + fileName);

		int rows = MAP_SIZE_HEIGHT / TILE_SIZE + 1;
		int columns = MAP_SIZE_WIDTH / TILE_SIZE;

		file << tagMapSize << MAP_SIZE_WIDTH << ";" << MAP_SIZE_HEIGHT << ";\n";
		for(int i = 0; i < rows; ++i){
			for(int j = 0; j < columns; ++j){
				if(tiles[i][j] != NULL){
					auto tileShape = tiles[i][j]->shape;
					TileConfigID id = tiles[i][j]->id;
					int posX = tileShape.getPosition().x;
					int posY = tileShape.getPosition().y;

					file << tagID << id << ";" << tagPosition << posX << ":" << posY << ";\n";
				}
			}
		}
		printf("Complete!\n");
		file.close();
		return 1;
	};
};