#pragma once
#include "CommonConstants.h"
#include "RunningContext.h"
#include "Character.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>


class TestGame:public RunningContext{
public:
	TestGame(){
		printf("Creating game window...\n");
		contextType = CONTEXT_GAME;
		worldInterface->setContextType(contextType);
		entityManager->setContextType(contextType);
		windowManager->setContextType(contextType);
		windowManager->createWindow();
	};

	~TestGame(){
		/*testWindow->close();
		delete testWindow;*/
	};

	RunningContextTypes getContextType(){
		return contextType;
	};

	CurrentViewport getCurrentViewport(){
		return character->getCurrentViewport();
	};

	void setCurrentViewport(CurrentViewport newViewport){
		character->setCurrentViewport(newViewport);
	};

	/*sf::View* getCamera(){
		return character->getCamera();
	};*/

	sf::Vector2f getCharacterPos(){
		return character->getPosition();
	};

	void loadMap(sf::Vector2f characterPos){
		worldInterface->getLoadedMapHeightAndWidth(LOADED_MAP_SIZE_HEIGHT, LOADED_MAP_SIZE_WIDTH);
		character = new Character(characterPos.x, characterPos.y, contextType);
		character->setCurrentWindow(windowManager->getWindow());
		entityManager->addEntity(character);
	};

	virtual Status update(float dt){
		entityManager->update();

		return RUNNING;
	};

private:
	int LOADED_MAP_SIZE_HEIGHT = 0;
	int LOADED_MAP_SIZE_WIDTH = 0;

protected:
	//TODO these things are protected in base class and how we handle them here should be redone
	Character* character = NULL;
};
