#pragma once
#include <stdio.h>
#include "Common.h"

int main(){
	sf::RenderWindow* currentWindow;

	RunningContextStack* contextStack = RunningContextStack::getInstance();
	contextStack->addRunningContext(CONTEXT_LEVEL_EDITOR);

	RunningContextsDeque* contexts = contextStack->getContexts();
	EventManager* eventManager = EventManager::getInstance();

	while(contexts->size() > 0){
		contexts = contextStack->getContexts();
		auto currentContext = contexts->front();
		currentWindow = currentContext->getWindow();

		currentWindow->clear();
		currentContext->update(0.f);
		currentWindow->display();

		eventManager->update();//think about doing this first
	}

	return 0;
};