#include "Entity.h"



Entity::Entity(){
}

Entity::~Entity(){
}

RunningContextTypes Entity::getContextType(){
	return contextType;
}

const sf::CircleShape* Entity::getShape(){
	return &shape;
}

void Entity::update(){
	PRINT_ERROR("Entity::modeLevelEditorUpdate", "calling base class!");
}
