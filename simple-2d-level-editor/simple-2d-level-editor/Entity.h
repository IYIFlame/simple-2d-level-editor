#pragma once
#include <SFML/Graphics.hpp>
#include "CommonConstants.h"
#include "CommonHelperFunctions.h"

class Entity{
protected:
	RunningContextTypes contextType = CONTEXT_INVALID;
	sf::CircleShape shape;//TODO change this to not be a circle shape for certain but a shape
public:
	Entity();
	virtual ~Entity();
	virtual RunningContextTypes getContextType();
	virtual const sf::CircleShape* getShape();
	virtual void update();
};

