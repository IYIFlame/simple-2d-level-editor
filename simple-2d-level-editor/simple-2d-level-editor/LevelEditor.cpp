#pragma once
#include "CommonConstants.h"
#include "RunningContext.h"
#include "Character.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

class LevelEditor:public RunningContext{
public:
	LevelEditor(){};
	LevelEditor(sf::RenderWindow* newWindow){
		window = newWindow;
		initMap();
	};
	virtual ~LevelEditor(){
		window->close();
		delete window;
	};

	sf::RenderWindow* getWindow(){
		return window;
	};

	RunningContextTypes getContextType(){
		return contextType;
	};

	CurrentViewport getCurrentViewport(){
		return currentViewport;
	};

	Status update(float dt){
		int rows = MAP_SIZE_HEIGHT / TILE_SIZE + 1;
		int columns = MAP_SIZE_WIDTH / TILE_SIZE;
		for(int i = 0; i < rows; ++i){
			for(int j = 0; j < columns; ++j){
				if(tiles[i][j] != NULL){
					window->draw(tiles[i][j]->shape);
				}
			}
		}

		//update not really needed at this time
		if(character != NULL){//change this
			character->modeLevelEditorUpdate();
			window->draw(character->shape);
		}

		return RUNNING;
	};

private:
	sf::RenderWindow* window = NULL;
	Character* character;
	RunningContextTypes contextType = CONTEXT_LEVEL_EDITOR;

	typedef std::vector< std::vector<Tile*> > Tiles;
	Tiles tiles;

	CurrentViewport currentViewport = DEFAULT;

	void applyTileConfig(int posX, int posY, TileConfigID tileConfigID){
		tiles[posY / TILE_SIZE][posX / TILE_SIZE]->applyTileConfig(TileConfigsCollectionGlobal[tileConfigID], CONTEXT_LEVEL_EDITOR);
	}

	void updateCharacter(int posX, int posY){
		sf::Vector2i position = sf::Mouse::getPosition(*window);
		if(character == NULL){
			character = new Character(posX - posX % TILE_SIZE, posY - posY % TILE_SIZE, CONTEXT_LEVEL_EDITOR);
			character->setCurrentWindow(window);
			printf("%d %d %d %d\n", posX, posY, posX / TILE_SIZE, posY / TILE_SIZE);
		}
		else{
			character->setStartPosition(posX - posX % TILE_SIZE, posY - posY % TILE_SIZE);
			printf("%d %d %d %d\n", posX, posY, posX / TILE_SIZE, posY / TILE_SIZE);
		}
	}

	void initMap(){
		int rows = MAP_SIZE_HEIGHT / TILE_SIZE + 1;
		int columns = MAP_SIZE_WIDTH / TILE_SIZE;
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
			tiles.push_back(row);
		}
	};

	const std::string pathName = "C:\\Users\\flame\\Source\\Repos\\simple-2d-level-editor\\simple-2d-level-editor\\simple-2d-level-editor\\";
	void exportMap(const std::string fileName){
		static const char tagMapSize = char(MAP_SIZE);
		static const char tagID = char(ID);
		static const char tagPosition = char(POSITION);

		printf("Exporting map...");
		std::ofstream file;
		file.open(pathName + fileName);

		int rows = MAP_SIZE_HEIGHT / TILE_SIZE + 1;
		int columns = MAP_SIZE_WIDTH / TILE_SIZE;

		file << tagMapSize << MAP_SIZE_WIDTH << ";" << MAP_SIZE_HEIGHT << ";\n";
		if(character != NULL){
			file << tagID << character->id << ";" << tagPosition << character->startPosition.x << ":" << character->startPosition.y << ";\n";
		}

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
	};
};