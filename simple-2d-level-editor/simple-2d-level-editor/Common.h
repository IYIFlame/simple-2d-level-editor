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
#include "WindowManager.h"

//static bool DISABLE_VIEWPORTS = false;

static sf::RenderWindow* createWindow(RunningContextTypes);
//use templates....
//also this should be a stack and we should use the last element, no need to be shifting things even if it's not that often
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

//move this to common constants if still needed
typedef std::vector<CurrentViewport> ViewportList;
static const ViewportList VIEWPORTS = {FIRST,SECOND,THIRD,FOURTH,DEFAULT,};

typedef std::deque<EventTypes> Events;
class EventManager{
private:
	static EventManager* _instance;
	static Events* events;
	static WindowManager* windowManager;
	EventManager(){};

public:
	static EventManager* getInstance();
	static Events* getEvents();
	static void update();
	static void checkEventsForEditor(WorldInterface*, RunningContext*);
	static void checkEventsForGame(WorldInterface*, RunningContext*);
	static void setWindowManager(WindowManager*);
};
