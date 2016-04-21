#include "RunningContext.h"

RunningContext::RunningContext(){};
RunningContext::~RunningContext(){};

Status RunningContext::update(float dt){
	PRINT_ERROR("RunningContextTypes:update", "calling base class update!");
	return RUNNING;
};

RunningContextTypes RunningContext::getContextType(){
	return contextType;
};

void RunningContext::importMap(const std::string){
	PRINT_ERROR("RunningContextTypes::exportMap", "calling base class export map!");
};

void RunningContext::exportMap(const std::string){
	PRINT_ERROR("RunningContextTypes::exportMap", "calling base class export map!");
};

void RunningContext::applyTileConfig(int, int, TileConfigID){
	PRINT_ERROR("RunningContextTypes::applyTileConfig", "calling base class applyTileConfig!");
};

void RunningContext::updateCharacter(int, int){
	PRINT_ERROR("RunningContext::updateCharacter", "calling base class updateCharacter!");
};

Tiles& RunningContext::getTiles(){
	PRINT_ERROR("RunningContext::getTiles", "calling base class getTiles!");
	return tiles;
}

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
