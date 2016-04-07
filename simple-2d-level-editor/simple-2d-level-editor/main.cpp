#pragma once
#include <stdio.h>
#include "Common.h"

#include "TestGame.cpp"
#include "LevelEditor.cpp"
#include "Character.h"

sf::RenderWindow* createWindow(RunningMode mode){
	if(mode == MODE_GAME){
		return new sf::RenderWindow(sf::VideoMode(GAME_RES_WIDTH, GAME_RES_HEIGHT), "FOCKEN OP GAEM M8");
	}
	else if(mode == MODE_LEVEL_EDITOR){
		return new sf::RenderWindow(sf::VideoMode(MAP_SIZE_WIDTH, MAP_SIZE_HEIGHT), "FOCKEN OP EDITOR M8");
	}
};

//TODO: think about adding a change window helper function as this is going to involve doing many things

int main(){
	sf::RenderWindow* levelEditorWindow = createWindow(MODE_LEVEL_EDITOR);
	sf::RenderWindow* testGameWindow = NULL;
	sf::RenderWindow* currentWindow = levelEditorWindow;

	LevelEditor* levelEditor = new LevelEditor(currentWindow);
	TestGame* testGame = NULL;
	Character* character = NULL;

	Status levelEditorStatus = RUNNING;
	Status testGameStatus = NOT_RUNNING;
	Status characterStatus = NOT_RUNNING;

	while(levelEditorStatus != EXITING){
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
				currentWindow->setView(currentWindow->getDefaultView());
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
		switch(characterStatus){
			case RUNNING:
				if(levelEditorStatus == RUNNING){
					if(sf::Mouse::isButtonPressed(sf::Mouse::Middle)){
						//change position
						sf::Vector2i position = sf::Mouse::getPosition(*currentWindow);
						printf("%d %d %d %d\n", position.x, position.y, position.x / TILE_SIZE, position.y / TILE_SIZE);
						character->setPosition(position.x - position.x%TILE_SIZE, position.y - position.y%TILE_SIZE);
					}
					characterStatus = character->modeLevelEditorUpdate(currentWindow);
				}
				else{
					characterStatus = character->modeGameUpdate(currentWindow);
				}
				break;
			case EXITING:
				character->~Character();
				character = NULL;
				characterStatus = NOT_RUNNING;
				break;
			case NOT_RUNNING:
				//create new character
				if(levelEditorStatus == RUNNING){
					if(sf::Mouse::isButtonPressed(sf::Mouse::Middle)){
						character = new Character();
						sf::Vector2i position = sf::Mouse::getPosition(*currentWindow);
						printf("%d %d %d %d\n", position.x, position.y, position.x / TILE_SIZE, position.y / TILE_SIZE);
						character->setPosition(position.x - position.x%TILE_SIZE, position.y - position.y%TILE_SIZE);
						characterStatus = RUNNING;
					}
				}
			default:
				break;
		}
		currentWindow->display();
	}

	currentWindow->close();
	levelEditorWindow = NULL;
	return 0;
}