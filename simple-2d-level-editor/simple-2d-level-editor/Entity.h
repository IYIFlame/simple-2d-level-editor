#pragma once
#include <SFML/Graphics.hpp>
#include "CommonConstants.h"

class Entity{
protected:
	RunningContextTypes contextType = CONTEXT_INVALID;
	sf::CircleShape shape;
public:
	Entity();
	virtual ~Entity();
	RunningContextTypes getContextType();
	const sf::CircleShape* getShape();
};

