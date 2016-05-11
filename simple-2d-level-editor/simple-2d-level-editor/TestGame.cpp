#pragma once
#include "CommonConstants.h"
#include "WorldInterface.h"
#include "RunningContext.h"
#include "Character.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>


class TestGame:public RunningContext{
public:
	TestGame(){
		contextType = CONTEXT_GAME;
		printf("creating window\n");
		windowManager->createWindow(contextType);
	};
	TestGame(sf::RenderWindow* newWindow){
		printf("creating window\n");
		//testWindow = newWindow;
	};
	~TestGame(){
		/*testWindow->close();
		delete testWindow;*/
	};
	/*sf::RenderWindow* getWindow(){
		return testWindow;
	};*/
	RunningContextTypes getContextType(){
		return contextType;
	};
	CurrentViewport getCurrentViewport(){
		return character->getCurrentViewport();
	};
	void setCurrentViewport(CurrentViewport newViewport){
		character->setCurrentViewport(newViewport);
	};
	sf::View* getCamera(){
		return character->getCamera();
	};
	sf::Vector2f getCharacterPos(){
		return character->getPosition();
	};

	void loadMap(sf::Vector2f characterPos){
		//tiles = worldInterface->getRunningContextTiles(contextType);
		worldInterface->getLoadedMapHeightAndWidth(LOADED_MAP_SIZE_HEIGHT, LOADED_MAP_SIZE_WIDTH);
		character = new Character(characterPos.x, characterPos.y, contextType);
		character->setCurrentWindow(windowManager->getWindow(contextType));
		entityManager->addEntity(character);
	};

	virtual Status update(float dt){
		////TODO: we should only draw the things that are visible to the camera not everything so use cameraPos
		//if(tiles != NULL){
		//	//(C1) these things should be done only once when loading a map instead of every tick...
		//	int rows = LOADED_MAP_SIZE_HEIGHT;
		//	int columns = LOADED_MAP_SIZE_WIDTH;
		//	getRowsAndCols(rows, columns);

		//	for(int i = 0; i < rows; ++i){
		//		for(int j = 0; j < columns; ++j){
		//			if((*tiles)[i][j] != NULL){
		//				testWindow->draw((*tiles)[i][j]->shape);
		//			}
		//		}
		//	}
		//}
		//if(character != NULL){
		//	character->modeGameUpdate();
		//	testWindow->draw(character->shape);
		//}		

		return RUNNING;
	};

private:
	int LOADED_MAP_SIZE_HEIGHT = 0;
	int LOADED_MAP_SIZE_WIDTH = 0;

protected:
	//TODO these things are protected in base class and how we handle them here should be redone
	//sf::RenderWindow* testWindow = NULL;
	Character* character = NULL;
	//RunningContextTypes contextType = CONTEXT_GAME;
	WorldInterface* worldInterface = WorldInterface::getInstance();
	//Tiles* tiles = NULL;
};
