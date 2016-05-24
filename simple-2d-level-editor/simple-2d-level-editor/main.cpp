#pragma once
#include <stdio.h>
#include "RunningContextStack.h"
#include "EventManager.h"

int main(){
	//sf::RenderWindow* currentWindow;
	RunningContextTypes contextType = CONTEXT_INVALID;
	RunningContext* currentContext = NULL;

	RunningContextStack* contextStack = new RunningContextStack();
	contextStack->addRunningContext(CONTEXT_LEVEL_EDITOR);

	RunningContextsDeque* contexts = contextStack->getContexts();
	currentContext = contexts->front();

	EventManager* eventManager = new EventManager();
	eventManager->setupContextManagers(currentContext->getWindowManager(), currentContext->getWorldInterface());// TODO: HMMMM...

	while(contexts->size() > 0){
		contexts = contextStack->getContexts();

		currentContext = contexts->front();
		contextType = currentContext->getContextType();

		currentContext->preUpdate();
		currentContext->update(0.f);
		currentContext->postUpdate();

		eventManager->update(contextStack);//think about doing this first
	}

	return 0;
};