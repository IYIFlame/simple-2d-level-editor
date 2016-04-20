#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <deque>

#include "CommonConstants.h"
#include "RunningContext.h"
#include "TestGame.cpp"
#include "LevelEditor.cpp"

//static bool DISABLE_VIEWPORTS = false;
static void PRINT_ERROR(std::string errorLocation, std::string errorMessage){
	printf("[%s] Error: %s\n", errorLocation, errorMessage);
};

static sf::RenderWindow* createWindow(RunningContextTypes);

typedef std::deque<RunningContext*> RunningContextsDeque;
class RunningContextStack{
private:
	static RunningContextStack* _instance;
	static RunningContextsDeque* contexts;
	RunningContextStack(){};

public:
	static RunningContextStack* getInstance();
	static RunningContextsDeque* getContexts();
	static void addRunningContext(RunningContextTypes);
	static void removeRunningContext(RunningContext*);
};

typedef std::vector<CurrentViewport> ViewportList;
static const ViewportList VIEWPORTS = {FIRST,SECOND,THIRD,FOURTH,DEFAULT,};

typedef std::deque<EventTypes> Events;
class EventManager{
private:
	static EventManager* _instance;
	static Events* events;
	EventManager(){};

public:
	static EventManager* getInstance();
	static Events* getEvents();
	static void update();
	static void checkEventsForEditor(RunningContext*);
	static void checkEventsForGame(RunningContext*);
};

static bool outOfWindowBounds(int x, int y, int maxWidth, int maxHeight){
	return maxWidth < x || x < 0 || maxHeight < y || y < 0;
};

static void getRowsAndCols(int& resHeight, int& resWidth){
	resHeight = resHeight / TILE_SIZE + 1;
	resWidth /= TILE_SIZE;
};