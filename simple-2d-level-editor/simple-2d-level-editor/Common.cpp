#include "Common.h"

EventQueue* EventQueue::_instance = NULL;
Events* EventQueue::events = NULL;
EventQueue* EventQueue::getInstance(){
	if(_instance == NULL)
		_instance = new EventQueue(); //Not thread-safe version
	return _instance;

	//Note that _instance is *never* deleted - 
	//it exists for the entire lifetime of the program!
}

Events* EventQueue::getEvents(){
	if(events == NULL)
		events = new Events();
	return events;
}
