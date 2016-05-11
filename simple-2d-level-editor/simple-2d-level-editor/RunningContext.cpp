#include "RunningContext.h"

RunningContext::RunningContext(){
	entityManager = new EntitiesManager();
	windowManager = new WindowManager(entityManager);
};
RunningContext::~RunningContext(){};

void RunningContext::preUpdate(){
	windowManager->preUpdate(contextType);
}

Status RunningContext::update(float dt){
	PRINT_ERROR("RunningContextTypes:update", "calling base class update!");
	return RUNNING;
};

void RunningContext::postUpdate(){
	windowManager->postUpdate(contextType);
}

RunningContextTypes RunningContext::getContextType(){
	return contextType;
};

void RunningContext::loadMap(sf::Vector2f charaacterPos){
	PRINT_ERROR("RunningContextTypes::loadMap", "calling base class loadMap!");
}

void RunningContext::updateCharacter(int, int){
	PRINT_ERROR("RunningContext::updateCharacter", "calling base class updateCharacter!");
};

sf::View* RunningContext::getCamera(){
	PRINT_ERROR("RunningContext::getCamera", "calling base class getCamera!");
	return camera;
}

Character* RunningContext::getCharacter(){
	PRINT_ERROR("RunningContext::getCharacter", "calling base class getCharacter!");
	return NULL;
}

void RunningContext::setCurrentViewport(CurrentViewport newViewport){
	PRINT_ERROR("RunningContext::setCurrentViewport", "calling base class setCurrentViewport!");
}

WindowManager* RunningContext::getWindowManager(){
	return windowManager;
}

EntitiesManager* RunningContext::getEntitiesManager(){
	return entityManager;
}
