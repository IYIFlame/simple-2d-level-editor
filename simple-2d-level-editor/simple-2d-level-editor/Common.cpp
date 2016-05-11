#include "Common.h"

static sf::RenderWindow* createWindow(RunningContextTypes mode){
	if(mode == CONTEXT_GAME){
		return new sf::RenderWindow(sf::VideoMode(GAME_RES_WIDTH, GAME_RES_HEIGHT), "BEST GAME");
	}
	else if(mode == CONTEXT_LEVEL_EDITOR){
		return new sf::RenderWindow(sf::VideoMode(MAP_SIZE_WIDTH, MAP_SIZE_HEIGHT), "BEST LEVEL EDITOR");
	}
};

//wouldnt be bad to create a template for this instead...
RunningContextStack* RunningContextStack::_instance = NULL;
RunningContextsDeque* RunningContextStack::contexts = new RunningContextsDeque();
RunningContextStack* RunningContextStack::getInstance(){
	if(_instance == NULL)
		_instance = new RunningContextStack(); //Not thread-safe version
	return _instance;

	//Note that _instance is *never* deleted - 
	//it exists for the entire lifetime of the program!
}

RunningContextsDeque* RunningContextStack::getContexts(){
	//if(contexts == NULL)
		//contexts = new RunningContextsDeque();
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
	//TODO oh god oh god oh god oh god oh god
	auto firstContext = contexts->front();
	if(firstContext != NULL){
		EventManager::getInstance()->setWindowManager(firstContext->getWindowManager());
	}
}

void RunningContextStack::removeRunningContext(RunningContext* context){
	if(context == contexts->front()){
		contexts->pop_front();
		context->~RunningContext();
	}
	//TODO oh god oh god oh god oh god oh god
	auto firstContext = contexts->front();
	if(firstContext != NULL){
		EventManager::getInstance()->setWindowManager(firstContext->getWindowManager());
	}
}

EventManager* EventManager::_instance = NULL;
Events* EventManager::events = NULL;
WindowManager* EventManager::windowManager = NULL;

EventManager* EventManager::getInstance(){
	if(_instance == NULL)
		_instance = new EventManager(); //Not thread-safe version
	return _instance;

	//Note that _instance is *never* deleted - 
	//it exists for the entire lifetime of the program!
}

Events* EventManager::getEvents(){
	if(events == NULL)
		events = new Events();
	return events;
}

void EventManager::setWindowManager(WindowManager* windowManager){
	EventManager::windowManager = windowManager;
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

//void EventManager::update(RunningContextsDeque* contexts){//add the world interface here later
void EventManager::update(){
	auto worldInterface = WorldInterface::getInstance();
	auto contexts = RunningContextStack::getContexts();
	if(contexts->size() > 0){
		RunningContextTypes currentContextType = contexts->front()->getContextType();
		RunningContext* currentContext;
		if(currentContextType == CONTEXT_LEVEL_EDITOR){
			currentContext = contexts->front();
			checkEventsForEditor(worldInterface, currentContext);
		}
		else if(currentContextType == CONTEXT_GAME){
			currentContext = contexts->front();
			checkEventsForGame(worldInterface, currentContext);
		}
		else{
			printf("[EventManager:update] Error: unknown running context type %d", currentContextType);
		}
	}
}

void EventManager::checkEventsForEditor(WorldInterface* worldInterface, RunningContext* context){
	sf::Event event;
	auto window = windowManager->getWindow(CONTEXT_LEVEL_EDITOR);
	if(window->pollEvent(event)){
		if(event.type == sf::Event::Closed){
			windowManager->destroyWindow(CONTEXT_LEVEL_EDITOR);
			RunningContextStack::removeRunningContext(context);
			return;
		}
		if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
			windowManager->destroyWindow(CONTEXT_LEVEL_EDITOR);
			RunningContextStack::removeRunningContext(context);
			return;
		}

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

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			std::string fileName = "test.txt";
			//context->exportMap(fileName);
			worldInterface->exportMap(fileName, context->getCharacter());
		}
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
			windowManager->createWindow(CONTEXT_GAME);
			RunningContextStack::addRunningContext(CONTEXT_GAME);
		}
	}
}

void EventManager::checkEventsForGame(WorldInterface* worldInterface, RunningContext* context){
	sf::Event event;
	auto window = windowManager->getWindow(CONTEXT_GAME);
	if(window->pollEvent(event)){
		if(event.type == sf::Event::Closed){
			windowManager->destroyWindow(CONTEXT_GAME);
			RunningContextStack::removeRunningContext(context);
			return;
		}
		if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
			windowManager->destroyWindow(CONTEXT_GAME);
			RunningContextStack::removeRunningContext(context);
			return;
		}

		sf::Vector2i position = sf::Mouse::getPosition(*window);
		int posX = position.x;
		int posY = position.y;

		if(outOfWindowBounds(posX, posY, GAME_RES_WIDTH, GAME_RES_HEIGHT)){
			return;
		}

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
	}
}
