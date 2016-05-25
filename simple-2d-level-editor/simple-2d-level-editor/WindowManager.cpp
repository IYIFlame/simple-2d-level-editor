#include "WindowManager.h"

WindowManager::WindowManager(){
}

WindowManager::WindowManager(RunningContextTypes contextType, WorldInterface* worldInterface, EntitiesManager* entityManager){
	this->contextType = contextType;
	this->worldInterface = worldInterface;
	this->entityManager = entityManager;
}

WindowManager::~WindowManager(){
	/*delete entityManager;
	delete worldInterface;*/

	runningContextWindow->close();
	delete runningContextWindow;
}

void WindowManager::setContextType(RunningContextTypes contextType){
	this->contextType = contextType;
}

void WindowManager::createWindow(){
	if(contextType == CONTEXT_GAME){
		runningContextWindow = new sf::RenderWindow(sf::VideoMode(GAME_RES_WIDTH, GAME_RES_HEIGHT), "BEST GAME");
	}
	else if(contextType == CONTEXT_LEVEL_EDITOR){
		runningContextWindow = new sf::RenderWindow(sf::VideoMode(MAP_SIZE_WIDTH, MAP_SIZE_HEIGHT), "BEST LEVEL EDITOR");
	}
	else{
		PRINT_ERROR("WindowManager::createWindow", "unknown context type received!");
	}
}

void WindowManager::destroyWindow(){
	runningContextWindow->close();
	runningContextWindow = NULL;
}

void WindowManager::preUpdate(){
	runningContextWindow->clear();
}

void WindowManager::postUpdate(){
	Tiles* tiles = NULL;
	Tile* tile = NULL;
	tiles = worldInterface->getRunningContextTiles();

	for(int i = 0; i < tiles->size(); ++i){
		for(int j = 0; j < (*tiles)[i].size(); ++j){
			tile = (*tiles)[i][j];
			runningContextWindow->draw(tile->shape);
		}
	}

	//here we would get all entities and draw them as well
	//for now we just call the character directly
	EntityCollection* entityCollection = entityManager->getEntityCollection();
	for(int i = 0; i < entityCollection->size(); ++i){
		Entity* entity = entityCollection->at(i);
		auto shape = entity->getShape();
		runningContextWindow->draw(*shape);
	}

	runningContextWindow->display();
}

sf::RenderWindow* WindowManager::getWindow(){
	return runningContextWindow;
}
