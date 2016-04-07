#include "Character.h"
#include <stdio.h>


Character::Character(){
	applyTileConfig(TileConfigsCollectionGlobal[CHARACTER], MODE_GAME);
	setPosition(0,0);
	camera = new sf::View (sf::Vector2f(position.x + cameraSize.x/2, position.y + cameraSize.y/2), cameraSize);
}


Character::~Character(){
}

void Character::applyTileConfig(TileConfig config, RunningMode mode){
	id = config.id;  
	shape.setFillColor(config.colour);
	if(mode == MODE_LEVEL_EDITOR){
		height = config.levelEditorSize.y;
		shape.setRadius(height/2);
	}
	else if(mode == MODE_GAME){
		height = config.inGameSize.y;
		shape.setRadius(height/2);
	}
}

Status Character::modeLevelEditorUpdate(sf::RenderWindow* currWindow){
	currWindow->setView(currWindow->getDefaultView());
	shape.setPosition(position.x, position.y);
	currWindow->draw(shape);
	return RUNNING;
}

Status Character::modeGameUpdate(sf::RenderWindow* currWindow){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		position.x += TILE_SIZE;
	}

	shape.setPosition(position.x, GAME_RES_HEIGHT - height - TILE_SIZE);
	sf::Vector2f shapePos = shape.getPosition();
	camera->setCenter(shapePos.x + cameraSize.x / 2, shapePos.y - cameraSize.y / 2 + height + TILE_SIZE);
	currWindow->setView(*camera);
	currWindow->draw(shape);
	return RUNNING;
}