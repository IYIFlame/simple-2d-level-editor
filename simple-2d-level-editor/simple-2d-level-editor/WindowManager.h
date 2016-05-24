#pragma once
#include <SFML/Graphics.hpp>
#include "CommonConstants.h"
#include "EntitiesManager.h"
#include "WorldInterface.h"
#include "TileLib.h"

class WindowManager{
	//for now we will only have one editor and one game at most running at the same time
	RunningContextTypes contextType = CONTEXT_INVALID;
	sf::RenderWindow* runningContextWindow = NULL;
	EntitiesManager* entityManager = NULL;
	WorldInterface* worldInterface = NULL;
public:
	WindowManager();

	WindowManager(RunningContextTypes, WorldInterface*, EntitiesManager*);
	//WindowManager(WorldInterface*, EntitiesManager*);

	~WindowManager();

	void setContextType(RunningContextTypes);

	void createWindow();

	void destroyWindow();

	void preUpdate();

	void postUpdate();

	sf::RenderWindow* getWindow();
};

