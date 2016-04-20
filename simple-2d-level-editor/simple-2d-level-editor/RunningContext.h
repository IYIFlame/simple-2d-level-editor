#pragma once
#include <SFML/Graphics.hpp>
#include "CommonConstants.h"

class RunningContext{
private:
	RunningContextTypes contextType = CONTEXT_INVALID;
public:
	RunningContext();
	virtual ~RunningContext();

	virtual Status update(float dt);

	virtual sf::RenderWindow* getWindow() = 0;

	virtual RunningContextTypes getContextType();

	virtual void exportMap(const std::string);

	virtual void applyTileConfig(int, int, TileConfigID);

	virtual void updateCharacter(int, int);
};

