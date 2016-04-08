#pragma once
#include <stdio.h>
#include "Common.h"

#include "TestGame.cpp"
#include "LevelEditor.cpp"

sf::RenderWindow* currentWindow;
Status levelEditorStatus;
Status testGameStatus;
Status characterStatus;

LevelEditor* levelEditor;
TestGame* testGame;

sf::RenderWindow* createWindow(RunningMode mode){
	if(mode == MODE_GAME){
		return new sf::RenderWindow(sf::VideoMode(GAME_RES_WIDTH, GAME_RES_HEIGHT), "FOCKEN OP GAEM M8");
	}
	else if(mode == MODE_LEVEL_EDITOR){
		return new sf::RenderWindow(sf::VideoMode(MAP_SIZE_WIDTH, MAP_SIZE_HEIGHT), "FOCKEN OP EDITOR M8");
	}
};

void setCurrentWindow(){};

void setCurrentViewport(sf::RenderWindow* window, CurrentViewport viewport){
	if(viewport == DEFAULT){
		currentWindow->setView(currentWindow->getDefaultView());
	}
	else{
		auto tiles = testGame->getTiles();
		int rows = GAME_RES_HEIGHT / TILE_SIZE + 1;
		int columns = GAME_RES_WIDTH / TILE_SIZE;
		for(int i = 0; i < rows; ++i){
			for(int j = 0; j < columns; ++j){
				if(tiles[i][j] != NULL){
					auto& tile = tiles[i][j];
					auto& shape = tile->shape;
					float x;
					switch(viewport){
						case (FIRST) :
							x = tile->position.x;
							break;
						case (SECOND) :
							x = tile->position.y + TILE_SIZE;
							break;
						case (THIRD) :
							x = GAME_RES_WIDTH - tile->position.x;
							break;
						case (FOURTH) :
							x = GAME_RES_HEIGHT - tile->position.y - TILE_SIZE;
							break;
					}
					shape.setPosition(x, GAME_RES_HEIGHT - tile->height);
				}
			}
		}
		sf::View* camera = testGame->getCamera();
		currentWindow->setView(*camera);
	}
};
void checkForEvents(){
	EventQueue* eventQueue = EventQueue::getInstance(); 
	Events* events = eventQueue->getEvents();
	while(events->size() > 0){
		EventTypes event = events->front();
		if(event == CHANGE_VIEWPORT){
			if(levelEditorStatus == RUNNING){
				setCurrentViewport(currentWindow, levelEditor->getCurrentViewport());
			}
			else if(testGameStatus == RUNNING){
				setCurrentViewport(currentWindow, testGame->getCurrentViewport());				
			}
		}
		events->pop_front();
	}
};

//TODO: think about adding a change window helper function as this is going to involve doing many things

int main(){
	sf::RenderWindow* levelEditorWindow = createWindow(MODE_LEVEL_EDITOR);
	sf::RenderWindow* testGameWindow = NULL;
	currentWindow = levelEditorWindow;

	levelEditor = new LevelEditor(currentWindow);
	testGame = NULL;

	levelEditorStatus = RUNNING;
	testGameStatus = NOT_RUNNING;
	characterStatus = NOT_RUNNING;

	while(levelEditorStatus != EXITING){
		checkForEvents();
		currentWindow->clear();
		switch(testGameStatus){
			case RUNNING:
				testGameStatus = testGame->update(0.f);
				break;
			case EXITING:
				//reset pointer
				currentWindow->close();
				testGameWindow = NULL;
				testGame->~TestGame();
				testGame = NULL;
				testGameStatus = NOT_RUNNING;
				currentWindow = levelEditorWindow;
				//currentWindow->setView(currentWindow->getDefaultView());
				break;
			case NOT_RUNNING:
				//check if should start new test
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
					printf("should start\n");
					testGameWindow = createWindow(MODE_GAME);
					currentWindow = testGameWindow;
					testGame = new TestGame(currentWindow);
					testGameStatus = RUNNING;
					levelEditorStatus = SUSPENDED;
					break;
				}
			default:
				levelEditorStatus = levelEditor->update();
		}
		currentWindow->display();
	}

	currentWindow->close();
	levelEditorWindow = NULL;
	return 0;
};