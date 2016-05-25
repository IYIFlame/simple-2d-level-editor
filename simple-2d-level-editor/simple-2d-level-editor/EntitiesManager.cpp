#include "EntitiesManager.h"

EntitiesManager::EntitiesManager(){};

EntitiesManager::EntitiesManager(RunningContextTypes contextType){
	this->contextType = contextType;
	entityCollection = new EntityCollection();
}

EntitiesManager::~EntitiesManager(){
	while(entityCollection->size()!= 0){
		Entity* entity = entityCollection->back();
		entityCollection->pop_back();
		delete entity;
	}
	delete entityCollection;
}

//TODO currently not checking if the entity is already in the collection
void EntitiesManager::addEntity(Entity* entity){
	entityCollection->push_back(entity);
}

void EntitiesManager::removeEntity(Entity* entity){
	int size = entityCollection->size();

	for(int i = 0; i < size; ++i){
		if(entityCollection->at(i) == entity){
			std::swap(entityCollection[i], entityCollection[size -1]);
			entityCollection->pop_back();
		}
	}
}

void EntitiesManager::setContextType(RunningContextTypes contextType){
	this->contextType = contextType;
}

//TODO change this when entity manager is fully implemeted as a per contextType system
void EntitiesManager::update(){
	for(int i = 0; i < entityCollection->size(); ++i){
		Entity* entity = entityCollection->at(i);
		entity->update();		
	}
}

EntityCollection* EntitiesManager::getEntityCollection(){
	return entityCollection;
}

void EntitiesManager::setCharacter(Entity* character){
	this->character = character;
}

Entity* EntitiesManager::getCharacter(){
	return character;
}
