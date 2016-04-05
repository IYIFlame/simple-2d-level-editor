#pragma once
#include <stdio.h>
#include "Common.h"

#include "TestGame.cpp"
#include "LevelEditor.cpp"



int main(){
	LevelEditor* levelEditor = new LevelEditor();
	TestGame* testGame = NULL;
	Status status = RUNNING;
	Status testGameStatus = NOT_RUNNING;

	while(status != EXITING){
		switch(testGameStatus){
			case RUNNING:
				testGameStatus = testGame->update(0.f);
				break;
			case EXITING:
				//reset pointer
				testGame = NULL;
				testGameStatus = NOT_RUNNING;
				break;
			case NOT_RUNNING:
				//check if should start new test
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
					printf("should start\n");
					testGame = new TestGame;
					testGameStatus = testGame->update(0.f);
					break;
				}
			default:
				status = levelEditor->update();
		}
	}
	return 0;
}