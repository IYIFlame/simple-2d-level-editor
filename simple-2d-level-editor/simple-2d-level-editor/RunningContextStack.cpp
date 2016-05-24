#include "RunningContextStack.h"

RunningContextStack::RunningContextStack(){
	contexts = new RunningContextsDeque();
}

RunningContextStack::~RunningContextStack(){
}

RunningContextsDeque* RunningContextStack::getContexts(){
	return contexts;
}

void RunningContextStack::addRunningContext(RunningContextTypes contextType){
	if(contextType == CONTEXT_LEVEL_EDITOR){
		//auto newWindow = createWindow(CONTEXT_LEVEL_EDITOR);
		contexts->push_front(new LevelEditor());
	}
	else if(contextType == CONTEXT_GAME){
		//auto newWindow = createWindow(CONTEXT_GAME);
		contexts->push_front(new TestGame());
	}
	else{
		PRINT_ERROR("RunningContextStack::addRunningContext", "invalid context type received");
	}
}

void RunningContextStack::removeRunningContext(RunningContext* context){
	if(context == contexts->front()){
		contexts->pop_front();
		delete context;
	}
}
