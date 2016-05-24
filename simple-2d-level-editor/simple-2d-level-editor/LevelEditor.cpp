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
	LevelEditor(){
		printf("Creating level editor window...\n");
		contextType = CONTEXT_LEVEL_EDITOR;
		worldInterface->setContextType(contextType);
		entityManager->setContextType(contextType);
		windowManager->setContextType(contextType);
		windowManager->createWindow();
		worldInterface->initMap();
	};

	~LevelEditor(){
		/*window->close();
		delete window;*/
	};

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
		//entityManager->update();

		return RUNNING;
	};

	void updateCharacter(int posX, int posY){
		if(character == NULL){
			character = new Character(posX - posX % TILE_SIZE, posY - posY % TILE_SIZE, CONTEXT_LEVEL_EDITOR);
			character->setCurrentWindow(windowManager->getWindow());
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

	Character* character = NULL;//TODO level editor should not know of entities such as character, only EntityManager
	CurrentViewport currentViewport = DEFAULT;//TODO not needed
};
