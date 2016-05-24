#pragma once
#include "CommonHelperFunctions.h"
#include "RunningContextStack.h"
#include "CommonConstants.h"
#include "RunningContext.h"
#include "WorldInterface.h"
#include "WindowManager.h"

class EventManager{
	WindowManager* windowManager = NULL;
	WorldInterface* worldInterface = NULL;
public:
	EventManager();

	~EventManager();

	void setupContextManagers(WindowManager*, WorldInterface*);

	void addRunningContext(RunningContextStack*, RunningContextTypes);

	void removeRunningContext(RunningContextStack*, RunningContext*);

	void update(RunningContextStack*);

	void checkEventsForEditor(RunningContextStack*, RunningContext*);

	void checkEventsForGame(RunningContextStack*, RunningContext*);
};
