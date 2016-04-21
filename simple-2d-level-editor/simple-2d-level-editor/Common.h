#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <deque>

#include "WorldInterface.h"
#include "CommonHelperFunctions.h"
#include "CommonConstants.h"
#include "RunningContext.h"
#include "TestGame.cpp"
#include "LevelEditor.cpp"

//static bool DISABLE_VIEWPORTS = false;

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
	static void checkEventsForEditor(WorldInterface*, RunningContext*);
	static void checkEventsForGame(WorldInterface*, RunningContext*);
};
