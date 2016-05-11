#pragma once
#include <SFML/Graphics.hpp>
#include "CommonConstants.h"
#include "EntitiesManager.h"
#include "WorldInterface.h"
#include "TileLib.h"
//#include "Character.h"

class WindowManager{
	//for now we will only have one editor and one game at most running at the same time
	sf::RenderWindow* runningContextWindows[2] = {NULL, NULL};
	EntitiesManager* entityManager = NULL;
public:
	WindowManager();
	WindowManager(EntitiesManager*);
	//WindowManager(WorldInterface*, EntitiesManager*);
	~WindowManager();
	void createWindow(const RunningContextTypes&);
	void destroyWindow(const RunningContextTypes&);
	void preUpdate(const RunningContextTypes&);
	void postUpdate(const RunningContextTypes&);
	sf::RenderWindow* getWindow(const RunningContextTypes&);
};

