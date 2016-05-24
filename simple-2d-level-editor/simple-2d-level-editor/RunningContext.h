#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h" //TODO not needed
#include "CommonConstants.h"
#include "CommonHelperFunctions.h"
#include "TileLib.h" //TODO not needed
#include "EntitiesManager.h"
#include "WindowManager.h"
#include "WorldInterface.h"

class RunningContext{
protected:
	//TODO: rename this class to entity manager...
	RunningContextTypes contextType = CONTEXT_INVALID;
	EntitiesManager* entityManager = NULL; 
	WindowManager* windowManager = NULL;
	WorldInterface* worldInterface = NULL;
	//sf::View* camera = NULL;//TODO also not needed?
	//Tiles tiles;//TODO not needed 
public://TODO revisit these functions and remove the unneeded ones
	RunningContext();

	virtual ~RunningContext();

	virtual void preUpdate();

	virtual Status update(float dt);

	virtual void postUpdate();

	virtual void setCurrentViewport(CurrentViewport newViewport);

	//virtual sf::View* getCamera();

	virtual Character* getCharacter();

	virtual CurrentViewport getCurrentViewport() =0;

	virtual RunningContextTypes getContextType();

	virtual WorldInterface* getWorldInterface();

	virtual WindowManager* getWindowManager();

	virtual EntitiesManager* getEntitiesManager();

	virtual void loadMap(sf::Vector2f);

	virtual void updateCharacter(int, int);
};

