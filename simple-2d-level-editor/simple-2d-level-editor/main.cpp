#pragma once
#include <stdio.h>

#include "TestGame.cpp"
#include "LevelEditor.cpp"



int main(){
	//change these to enums later on with NOT_RUNNING, RUNNING and EXITING
	int status = 0; // 0 = isOke, 1 = exit
	int testGameStatus = 0; //0 = uninitialized, 1 = isOke, 2 = exit
	LevelEditor* levelEditor = new LevelEditor();
	TestGame* testGame = NULL;

	while(status != 1){
		switch(testGameStatus){
			case 1:
				testGameStatus = testGame->update(0.f);
				break;
			case 2:
				//reset pointer
				testGame = NULL;
				testGameStatus = 0;
				break;
			case 0:
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