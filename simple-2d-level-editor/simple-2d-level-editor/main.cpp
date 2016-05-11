#pragma once
#include <stdio.h>
#include "Common.h"

int main(){
	//sf::RenderWindow* currentWindow;

	RunningContextStack* contextStack = RunningContextStack::getInstance();
	contextStack->addRunningContext(CONTEXT_LEVEL_EDITOR);

	RunningContextsDeque* contexts = contextStack->getContexts();
	EventManager* eventManager = EventManager::getInstance();

	RunningContextTypes contextType = CONTEXT_INVALID;

	while(contexts->size() > 0){
		contexts = contextStack->getContexts();
		auto currentContext = contexts->front();
		//currentWindow = currentContext->getWindow();

		//currentWindow->clear();
		contextType = currentContext->getContextType();
		currentContext->preUpdate();
		currentContext->update(0.f);
		//currentWindow->display();
		currentContext->postUpdate();

		eventManager->update();//think about doing this first
	}

	return 0;
};