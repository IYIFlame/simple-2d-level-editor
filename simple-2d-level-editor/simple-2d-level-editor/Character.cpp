#include "Character.h"
#include <stdio.h>


Character::Character(){
	applyTileConfig(TileConfigsCollectionGlobal[CHARACTER], CONTEXT_GAME);
}

Character::Character(float startPosX, float startPosY, RunningContextTypes mode){
	applyTileConfig(TileConfigsCollectionGlobal[CHARACTER], CONTEXT_GAME);
	setStartPosition(startPosX, startPosY);
	resetPosition();
	applyRunningModeSettings(mode);
}

Character::~Character(){
}

void Character::applyTileConfig(TileConfig config, RunningContextTypes mode){
	id = config.id;  
	shape.setFillColor(config.colour);
	if(mode == CONTEXT_LEVEL_EDITOR){
		height = config.levelEditorSize.y;
		shape.setRadius(height/2);
	}
	else if(mode == CONTEXT_GAME){
		height = config.inGameSize.y;
		shape.setRadius(height/2);
	}
}

void Character::applyRunningModeSettings(RunningContextTypes mode){
	if(camera == NULL){
		camera = new sf::View(sf::Vector2f(position.x + cameraSize.x / 2, position.y + cameraSize.y / 2), cameraSize);
	}
	if(mode == CONTEXT_LEVEL_EDITOR){
		shape.setPosition(startPosition.x, startPosition.y);		
		setCurrentViewport(DEFAULT);
	}
	else if(mode == CONTEXT_GAME){
		//game = newGame;
		setCurrentViewport(FIRST);
		sf::Vector2f pos = shape.getPosition();
		camera->setCenter(pos.x - TILE_SIZE * 2 + cameraSize.x / 2, pos.y - cameraSize.y / 2 + height + TILE_SIZE);
	}
}
//TODO: redo this horribleness!!!!
void Character::setCurrentViewport(CurrentViewport newViewport){
	currentViewport = newViewport;

	float x = position.x;
	float y = GAME_RES_HEIGHT - height - TILE_SIZE;
	
	switch(currentViewport){
		case (FIRST) :
			x = position.x;
			break;
		case (SECOND) :
			x = position.y;
			break;
		case (THIRD) :
			x = GAME_RES_WIDTH - position.x - TILE_SIZE;
			break;
		case (FOURTH) :
			x = GAME_RES_WIDTH - position.y - TILE_SIZE;
			break;
		default:
			x = position.x;
			y = position.y;
	}
	shape.setPosition(x, y);
	camera->setCenter(x - TILE_SIZE*2 + cameraSize.x / 2, y - cameraSize.y / 2 + height + TILE_SIZE);
}

void Character::setPosition(float x, float y){ 
	position.x = x; 
	position.y = y; 
}

void Character::setStartPosition(float x, float y){
	startPosition.x = x; 
	startPosition.y = y;
	resetPosition();
}

void Character::move(sf::Vector2f direction){
	position += direction;
	sf::Vector2f pos = sf::Vector2f(position.x, GAME_RES_HEIGHT - height - TILE_SIZE);
	shape.setPosition(pos);
	camera->setCenter(pos.x + cameraSize.x / 2, pos.y - cameraSize.y / 2 + height + TILE_SIZE);	
}

Status Character::modeLevelEditorUpdate(){
	//currWindow->draw(shape);
	shape.setPosition(startPosition);
	return RUNNING;
}

Status Character::modeGameUpdate(){
	sf::Event event;
	if(currWindow->pollEvent(event)){
		if(event.type == sf::Event::KeyPressed){
			if(event.key.code == sf::Keyboard::D){
				move(sf::Vector2f(TILE_SIZE, 0));
			}
		}
	}


	sf::Vector2f pos = shape.getPosition();
	//camera->setCenter(pos.x - TILE_SIZE*2 + cameraSize.x / 2, pos.y - cameraSize.y / 2 + height + TILE_SIZE);


	return RUNNING;
}