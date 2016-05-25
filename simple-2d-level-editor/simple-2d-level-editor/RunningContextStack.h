#pragma once
#include <SFML/Graphics.hpp>
//#include <map>
//#include <vector>
#include <deque>

//#include "WorldInterface.h"
#include "CommonHelperFunctions.h"
#include "CommonConstants.h"
//#include "RunningContext.h"
#include "TestGame.cpp"
#include "LevelEditor.cpp"
//#include "WindowManager.h"

//also this should be a stack and we should use the last element, no need to be shifting things even if it's not that often
typedef std::deque<RunningContext*> RunningContextsDeque;

class RunningContextStack{
	RunningContextsDeque* contexts = NULL;

public:
	RunningContextStack();

	~RunningContextStack();

	RunningContextsDeque* getContexts();

	void addRunningContext(RunningContextTypes);

	void removeRunningContext(RunningContext*);
};

//move this to common constants if still needed
//typedef std::vector<CurrentViewport> ViewportList;
//static const ViewportList VIEWPORTS = {FIRST,SECOND,THIRD,FOURTH,DEFAULT,};
