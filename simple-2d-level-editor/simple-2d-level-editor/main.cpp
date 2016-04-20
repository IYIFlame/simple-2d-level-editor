#pragma once
#include <stdio.h>
#include "Common.h"


//Status levelEditorStatus;
//Status testGameStatus;

//LevelEditor* levelEditor;
//TestGame* testGame;

//void setCurrentViewport(sf::RenderWindow* window, CurrentViewport viewport){
//	if(viewport == DEFAULT){
//		currentWindow->setView(currentWindow->getDefaultView());
//	}
//	else{
//		auto tiles = testGame->getTiles();
//		int rows = MAP_SIZE_HEIGHT;
//		int columns = MAP_SIZE_WIDTH;
//		getRowsAndCols(rows, columns);
//
//		for(int i = 0; i < rows; ++i){
//			for(int j = 0; j < columns; ++j){
//				if(tiles[i][j] != NULL){
//					auto& tile = tiles[i][j];
//					auto& shape = tile->shape;
//					float x;
//					switch(viewport){
//						case (FIRST) :
//							x = tile->position.x;
//							break;
//						case (SECOND) :
//							x = tile->position.y;
//							break;
//						case (THIRD) :
//							x = GAME_RES_WIDTH - tile->position.x - TILE_SIZE;
//							break;
//						case (FOURTH) :
//							x = GAME_RES_WIDTH - tile->position.y - TILE_SIZE;
//							break;
//					}
//					shape.setPosition(x, GAME_RES_HEIGHT - tile->height);
//				}
//			}
//		}
//		sf::View* camera = testGame->getCamera();
//		currentWindow->setView(*camera);
//	}
//};

//void checkForEvents(){
//	EventManager* eventQueue = EventManager::getInstance(); 
//	Events* events = eventQueue->getEvents();
//	while(events->size() > 0){
//		EventTypes event = events->front();
//		if(event == CHANGE_VIEWPORT){
//			if(levelEditorStatus == RUNNING){
//				setCurrentViewport(currentWindow, levelEditor->getCurrentViewport());
//			}
//			else if(testGameStatus == RUNNING){
//				setCurrentViewport(currentWindow, testGame->getCurrentViewport());				
//			}
//		}
//		events->pop_front();
//	}
//};

//TODO: think about adding a change window helper function as this is going to involve doing many things

int main(){
	//sf::RenderWindow* levelEditorWindow = createWindow(CONTEXT_LEVEL_EDITOR);
	//sf::RenderWindow* testGameWindow = NULL;
	sf::RenderWindow* currentWindow;

	RunningContextStack* contextStack = RunningContextStack::getInstance();
	contextStack->addRunningContext(CONTEXT_LEVEL_EDITOR);

	RunningContextsDeque* contexts = contextStack->getContexts();
	EventManager* eventManager = EventManager::getInstance();

	//levelEditor = new LevelEditor(currentWindow);

	//contexts->push_front(new LevelEditor(currentWindow));
	
	//testGame = NULL;

	//levelEditorStatus = RUNNING;
	//testGameStatus = NOT_RUNNING;

	//while(levelEditorStatus != EXITING){
	while(contexts->size() > 0){
		contexts = contextStack->getContexts();
		auto currentContext = contexts->front();
		currentWindow = currentContext->getWindow();

		currentWindow->clear();
		//switch(testGameStatus){
		//	case RUNNING:
		//		testGameStatus = currentContext->update(0.f);
		//		break;
		//	case EXITING:
		//		//reset pointer
		//		currentWindow->close();
		//		testGameWindow = NULL;
		//		//currentContext->~TestGame();

		//		contexts->pop_front();
		//		currentContext = contexts->front();
		//		testGameStatus = NOT_RUNNING;
		//		break;
		//	case NOT_RUNNING:
		//		//check if should start new test
		//		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
		//			printf("should start\n");
		//			testGameWindow = createWindow(CONTEXT_GAME);
		//			contexts->push_front(new TestGame(testGameWindow));
		//			currentContext = contexts->front();

		//			currentWindow = currentContext->getWindow();
		//			testGameStatus = RUNNING;
		//			levelEditorStatus = SUSPENDED;
		//			break;
		//		}
		//	default:
		//		auto editor = contexts->front();
		//		levelEditorStatus = editor->update(0.f);
		//}
		currentContext->update(0.f);
		currentWindow->display();

		eventManager->update();
	}

	//currentWindow->close();
	//levelEditorWindow = NULL;
	return 0;
};