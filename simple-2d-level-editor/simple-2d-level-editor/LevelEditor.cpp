#pragma once
#include "Common.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

class LevelEditor{
public:
	LevelEditor(){
		window = new sf::RenderWindow(sf::VideoMode(MAP_SIZE_WIDTH, MAP_SIZE_HEIGHT), "FOCKEN OP EDITOR M8");
		initMap();
	};
	~LevelEditor(){
		delete window;
	};

	Status update(){
		sf::Event event;
		if(window->pollEvent(event)){
			if(event.type == sf::Event::Closed){
				window->close();
				return EXITING;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				window->close();
				return EXITING;
			}

			sf::Vector2i position = sf::Mouse::getPosition(*window);
			int posX = position.x;
			int posY = position.y;

			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				printf("%d %d %d %d\n", position.x, position.y, position.x / TILE_SIZE, position.y / TILE_SIZE);
				tiles[posY / TILE_SIZE][posX / TILE_SIZE]->applyTileConfig(TileConfig_Green());
			}

			if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
				printf("%d %d %d %d\n", position.x, position.y, position.x / TILE_SIZE, position.y / TILE_SIZE);
				tiles[posY / TILE_SIZE][posX / TILE_SIZE]->applyTileConfig(TileConfig_Red());
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
				std::string fileName = "test.txt";
				exportMap(fileName);
			}

		}

		window->clear();
		int rows = MAP_SIZE_HEIGHT / TILE_SIZE + 1;
		int columns = MAP_SIZE_WIDTH / TILE_SIZE;
		for(int i = 0; i < rows; ++i){
			for(int j = 0; j < columns; ++j){
				if(tiles[i][j] != NULL){
					window->draw(tiles[i][j]->shape);
				}
			}
		}
		window->display();
		
		return RUNNING;
	};

private:
	sf::RenderWindow* window = NULL;

	typedef std::vector< std::vector<Tile*> > Tiles;
	Tiles tiles;

	const unsigned int MAP_SIZE_WIDTH = 800;
	const unsigned int MAP_SIZE_HEIGHT = 600;

	void initMap(){
		int rows = MAP_SIZE_HEIGHT / TILE_SIZE + 1;
		int columns = MAP_SIZE_WIDTH / TILE_SIZE;
		printf("rows %d columns %d\n", rows, columns);
		for(int i = 0; i < rows; ++i){
			std::vector<Tile*> row;

			for(int j = 0; j < columns; ++j){
				Tile* tile = new Tile();
				tile->applyTileConfig(TileConfig_Green());
				tile->shape.setPosition(sf::Vector2f(j * TILE_SIZE, i * TILE_SIZE));
				printf("y %d x %d\n", j * TILE_SIZE, i * TILE_SIZE);
				row.push_back(tile);
			}
			tiles.push_back(row);
		}
	};

	const std::string pathName = "C:\\Users\\flame\\Source\\Repos\\simple-2d-level-editor\\simple-2d-level-editor\\simple-2d-level-editor\\";
	int exportMap(const std::string fileName){
		printf("Exporting map...");
		std::ofstream file;
		file.open(pathName + fileName);

		int rows = MAP_SIZE_HEIGHT / TILE_SIZE + 1;
		int columns = MAP_SIZE_WIDTH / TILE_SIZE;

		using namespace std;
		file << to_string(MAP_SIZE) << MAP_SIZE_WIDTH << ";" << MAP_SIZE_HEIGHT << ";\n";
		for(int i = 0; i < rows; ++i){
			for(int j = 0; j < columns; ++j){
				if(tiles[i][j] != NULL){
					auto tileShape = tiles[i][j]->shape;
					TileConfigID id = tiles[i][j]->id;
					int posX = tileShape.getPosition().x;
					int posY = tileShape.getPosition().y;

					file << to_string(ID) << id << ";" << to_string(POSITION) << posX << ":" << posY << ";\n";
				}
			}
		}
		printf("Complete!\n");
		file.close();
		return 1;
	};
};