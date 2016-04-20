#include "RunningContext.h"

RunningContext::RunningContext(){};
RunningContext::~RunningContext(){};

Status RunningContext::update(float dt){
	//PRINT_ERROR("RunningContextTypes:update", "calling base class update!");
	return RUNNING;
};

RunningContextTypes RunningContext::getContextType(){
	return contextType;
};

void RunningContext::exportMap(const std::string){
	//PRINT_ERROR("RunningContextTypes::exportMap", "calling base class export map!");
};

void RunningContext::applyTileConfig(int, int, TileConfigID){
	//PRINT_ERROR("RunningContextTypes::applyTileConfig", "calling base class applyTileConfig!");
};

void RunningContext::updateCharacter(int, int){
	//PRINT_ERROR("RunningContext::updateCharacter", "calling base class updateCharacter!");
};

