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
		auto newWindow = createWindow(CONTEXT_LEVEL_EDITOR);
		contexts->push_front(new LevelEditor(newWindow));
	}
	else if(contextType == CONTEXT_GAME){
		auto newWindow = createWindow(CONTEXT_GAME);
		contexts->push_front(new TestGame(newWindow));	
	}
	else{
		PRINT_ERROR("RunningContextStack::addRunningContext", "invalid context type received");
	}
}

void RunningContextStack::removeRunningContext(RunningContext* context){
	if(context == contexts->front()){
		contexts->pop_front();
		context->~RunningContext();
	}
}

EventManager* EventManager::_instance = NULL;
Events* EventManager::events = NULL;
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

void EventManager::update(){
	auto contexts = RunningContextStack::getContexts();
	if(contexts->size() > 0){
		RunningContextTypes currentContextType = contexts->front()->getContextType();
		RunningContext* currentContext;
		if(currentContextType == CONTEXT_LEVEL_EDITOR){
			currentContext = contexts->front();
			checkEventsForEditor(currentContext);
		}
		else if(currentContextType == CONTEXT_GAME){
			currentContext = contexts->front();
			checkEventsForGame(currentContext);
		}
		else{
			printf("[EventManager:update] Error: unknown running context type %d", currentContextType);
		}
	}
}

void EventManager::checkEventsForEditor(RunningContext* context){
	sf::Event event;
	auto window = context->getWindow();
	if(window->pollEvent(event)){
		if(event.type == sf::Event::Closed){
			RunningContextStack::removeRunningContext(context);
			return;
		}
		if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
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
			context->applyTileConfig(posX, posY, GREEN);
		}

		if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
			printf("%d %d %d %d\n", position.x, position.y, position.x / TILE_SIZE, position.y / TILE_SIZE);
			context->applyTileConfig(posX, posY, RED);
		}

		if(sf::Mouse::isButtonPressed(sf::Mouse::Middle)){
			context->updateCharacter(posX, posY);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			std::string fileName = "test.txt";
			context->exportMap(fileName);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
			RunningContextStack::addRunningContext(CONTEXT_GAME);
		}
	}
}

void EventManager::checkEventsForGame(RunningContext* context){
	sf::Event event;
	auto window = context->getWindow();
	if(window->pollEvent(event)){
		if(event.type == sf::Event::Closed){
			RunningContextStack::removeRunningContext(context);
			return;
		}
		if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
			RunningContextStack::removeRunningContext(context);
			return;
		}

		sf::Vector2i position = sf::Mouse::getPosition(*window);
		int posX = position.x;
		int posY = position.y;

		if(outOfWindowBounds(posX, posY, MAP_SIZE_WIDTH, MAP_SIZE_HEIGHT)){
			return;
		}
	}
}
