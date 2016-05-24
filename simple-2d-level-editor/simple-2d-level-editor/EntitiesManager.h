#pragma once
#include "Entity.h"
#include <vector>
#include "CommonConstants.h"

//we will have a collection of entities for each context type
//TODO: this collection needs to be changed to something with O1 insert AND delete for when we have the light probes
typedef std::vector<Entity*> EntityCollection;
//typedef std::vector< EntityCollection* > Entities;

class EntitiesManager{
	EntityCollection* entityCollection = NULL;
	Entity* character = NULL;
	RunningContextTypes contextType = CONTEXT_INVALID;
public:
	EntitiesManager();

	EntitiesManager(RunningContextTypes);

	~EntitiesManager();

	void addEntity(Entity*);

	void removeEntity(Entity*);

	void setContextType(RunningContextTypes);

	void update();

	void setCharacter(Entity*);

	Entity* getCharacter();

	EntityCollection* getEntityCollection();

};

