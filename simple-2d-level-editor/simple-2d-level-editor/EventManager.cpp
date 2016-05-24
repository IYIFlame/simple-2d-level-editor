#include "EventManager.h"

EventManager::EventManager(){
}

EventManager::~EventManager(){
}

void EventManager::setupContextManagers(WindowManager* windowManager, WorldInterface* worldInterface){
	if(windowManager == NULL || worldInterface == NULL){
		PRINT_ERROR("EventManager::setupContextManagers", "received NULL for one of the managers");
		return;
	}

	this->windowManager = windowManager;
	this->worldInterface = worldInterface;
}

void EventManager::addRunningContext(RunningContextStack* contextStack, RunningContextTypes contextType){
	contextStack->addRunningContext(contextType);

	RunningContextsDeque* contexts = contextStack->getContexts();
	if(contexts->size() > 0){
		RunningContext* firstContext = contexts->front();
		setupContextManagers(firstContext->getWindowManager(), firstContext->getWorldInterface());
	}
}

void EventManager::removeRunningContext(RunningContextStack* contextStack, RunningContext* context){
	contextStack->removeRunningContext(context);

	RunningContextsDeque* contexts = contextStack->getContexts();
	if(contexts->size() > 0){
		RunningContext* firstContext = contexts->front();//TODO when empty this throws an exception.....
		setupContextManagers(firstContext->getWindowManager(), firstContext->getWorldInterface());
	}
}

void setCurrentViewport(RunningContext* context, CurrentViewport viewport){
	//auto window = context->getWindowManager()->getWindow(context->getContextType());
	if(viewport == DEFAULT){
		//window->setView(window->getDefaultView());
	}
	else{
		//auto tiles = context->getTiles();
		//int rows = MAP_SIZE_HEIGHT;
		//int columns = MAP_SIZE_WIDTH;
		//getRowsAndCols(rows, columns);

		//for(int i = 0; i < rows; ++i){
		//	for(int j = 0; j < columns; ++j){
		//		if(tiles[i][j] != NULL){
		//			auto& tile = tiles[i][j];
		//			auto& shape = tile->shape;
		//			float x;
		//			switch(viewport){
		//				case (FIRST) :
		//					x = tile->position.x;
		//					break;
		//				case (SECOND) :
		//					x = tile->position.y;
		//					break;
		//				case (THIRD) :
		//					x = GAME_RES_WIDTH - tile->position.x - TILE_SIZE;
		//					break;
		//				case (FOURTH) :
		//					x = GAME_RES_WIDTH - tile->position.y - TILE_SIZE;
		//					break;
		//			}
		//			shape.setPosition(x, GAME_RES_HEIGHT - tile->height);
		//		}
		//	}
		//}
		//sf::View* camera = context->getCamera();
		////window->setView(*camera);
		//context->setCurrentViewport(viewport);
	}
}

void EventManager::update(RunningContextStack* contextStack){
	RunningContextsDeque* contexts = contextStack->getContexts();
	if(contexts->size() > 0){
		RunningContextTypes currentContextType = contexts->front()->getContextType();
		RunningContext* currentContext;
		if(currentContextType == CONTEXT_LEVEL_EDITOR){
			currentContext = contexts->front();
			checkEventsForEditor(contextStack, currentContext);
		}
		else if(currentContextType == CONTEXT_GAME){
			currentContext = contexts->front();
			checkEventsForGame(contextStack, currentContext);
		}
		else{
			PRINT_ERROR("EventManager::update", "unknown running context type");
		}
	}
}

void EventManager::checkEventsForEditor(RunningContextStack* contextStack, RunningContext* context){
	sf::Event event;
	auto window = windowManager->getWindow();
	if(window->pollEvent(event)){
		if(event.type == sf::Event::Closed){
			removeRunningContext(contextStack, context);
			return;
		}
		if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
			removeRunningContext(contextStack, context);
			return;
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			std::string fileName = "test.txt";
			//context->exportMap(fileName);
			worldInterface->exportMap(fileName, context->getCharacter());
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
			//windowManager->createWindow(CONTEXT_GAME);
			addRunningContext(contextStack, CONTEXT_GAME);
		}

		//below this point is the code that should be executed only if the mouse is inside the window

		sf::Vector2i position = sf::Mouse::getPosition(*window);
		int posX = position.x;
		int posY = position.y;

		if(outOfWindowBounds(posX, posY, MAP_SIZE_WIDTH, MAP_SIZE_HEIGHT)){
			return;
		}

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			printf("%d %d %d %d\n", position.x, position.y, position.x / TILE_SIZE, position.y / TILE_SIZE);
			//context->applyTileConfig(posX, posY, GREEN);
			worldInterface->applyTileConfig(posX, posY, GREEN);
		}

		if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
			printf("%d %d %d %d\n", position.x, position.y, position.x / TILE_SIZE, position.y / TILE_SIZE);
			//context->applyTileConfig(posX, posY, RED);
			worldInterface->applyTileConfig(posX, posY, RED);
		}

		if(sf::Mouse::isButtonPressed(sf::Mouse::Middle)){
			context->updateCharacter(posX, posY);
		}
	}
}

void EventManager::checkEventsForGame(RunningContextStack* contextStack, RunningContext* context){
	sf::Event event;
	auto window = windowManager->getWindow();
	if(window->pollEvent(event)){
		if(event.type == sf::Event::Closed){
			removeRunningContext(contextStack, context);
			return;
		}
		if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
			removeRunningContext(contextStack, context);
			return;
		}

		//WorldInterface* worldInterface = context->getWorldInterface();

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
			std::string fileName = "test.txt";
			sf::Vector2f characterPos = worldInterface->importMap(fileName);
			context->loadMap(characterPos);
		}
		/*
		if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q){
		CurrentViewport currentViewport = context->getCurrentViewport();
		unsigned int newViewport = (currentViewport + NUMBER_OF_VIEWPORTS + 1) % NUMBER_OF_VIEWPORTS;
		printf("asd %d\n", newViewport);
		setCurrentViewport(context, VIEWPORTS[newViewport]);
		}

		if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E){
		//-1
		CurrentViewport currentViewport = context->getCurrentViewport();
		unsigned int newViewport = (currentViewport + NUMBER_OF_VIEWPORTS - 1) % NUMBER_OF_VIEWPORTS;
		printf("asd %d\n", newViewport);
		setCurrentViewport(context, VIEWPORTS[newViewport]);
		}*/

		//below this point is the code that should be executed only if the mouse is inside the window

		sf::Vector2i position = sf::Mouse::getPosition(*window);
		int posX = position.x;
		int posY = position.y;

		if(outOfWindowBounds(posX, posY, GAME_RES_WIDTH, GAME_RES_HEIGHT)){
			return;
		}
	}
}