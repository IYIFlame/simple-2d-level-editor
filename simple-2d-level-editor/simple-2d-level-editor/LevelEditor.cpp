#pragma once
#include "WorldInterface.h"
#include "CommonConstants.h"
#include "RunningContext.h"
#include "Character.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

class LevelEditor:public RunningContext{
public:
	LevelEditor(){
		contextType = CONTEXT_LEVEL_EDITOR;
		windowManager->createWindow(contextType);
		worldInterface->initMap();
	};
	//LevelEditor(sf::RenderWindow* newWindow){
	//	window = newWindow;
	//	worldInterface->initMap();
	//	//tiles = worldInterface->getRunningContextTiles(contextType);
	//};
	~LevelEditor(){
		/*window->close();
		delete window;*/
	};

	/*sf::RenderWindow* getWindow(){
		return window;
	};*/

	RunningContextTypes getContextType(){
		return contextType;
	};

	Character* getCharacter(){
		return character;
	};

	CurrentViewport getCurrentViewport(){
		return currentViewport;
	};

	Status update(float dt){
		//int rows = MAP_SIZE_HEIGHT / TILE_SIZE + 1;
		//int columns = MAP_SIZE_WIDTH / TILE_SIZE;
		//for(int i = 0; i < rows; ++i){
		//	for(int j = 0; j < columns; ++j){
		//		if((*tiles)[i][j] != NULL){
		//			window->draw((*tiles)[i][j]->shape);
		//		}
		//	}
		//}

		////update not really needed at this time
		//if(character != NULL){//change this
		//	character->modeLevelEditorUpdate();
		//	window->draw(character->shape);
		//}

		return RUNNING;
	};

	void updateCharacter(int posX, int posY){
		if(character == NULL){
			character = new Character(posX - posX % TILE_SIZE, posY - posY % TILE_SIZE, CONTEXT_LEVEL_EDITOR);
			character->setCurrentWindow(windowManager->getWindow(contextType));
			printf("%d %d %d %d\n", posX, posY, posX / TILE_SIZE, posY / TILE_SIZE);
			entityManager->addEntity(character);
		}
		else{
			character->setStartPosition(posX - posX % TILE_SIZE, posY - posY % TILE_SIZE);
			printf("%d %d %d %d\n", posX, posY, posX / TILE_SIZE, posY / TILE_SIZE);
		}
	}

protected:
	//TODO these things are protected in base class and how we handle them here should be redone

	//sf::RenderWindow* window = NULL;
	Character* character = NULL;
	//RunningContextTypes contextType = CONTEXT_LEVEL_EDITOR;

	WorldInterface* worldInterface = WorldInterface::getInstance();

	//Tiles* tiles;
	CurrentViewport currentViewport = DEFAULT;
};
